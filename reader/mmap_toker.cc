#include "reader/mmap_toker.h"

#include <cctype>
#include <cerrno>
#include <concepts>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

namespace iobench {
namespace {
struct MappedFile {
  const int fd;
  std::size_t position;
  const std::size_t length;
  char *contents;

  [[nodiscard]] inline bool valid_position() const { return position < length; }
  [[nodiscard]] inline char current() const { return contents[position]; }
  inline void advance() { ++position; }
};

inline int open_file(const std::string &filename) { return open(filename.c_str(), O_RDONLY); }

inline std::size_t file_size(const int fd) {
  struct stat file_info {};
  fstat(fd, &file_info);
  return static_cast<std::size_t>(file_info.st_size);
}

inline MappedFile mmap_file_from_disk(const std::string &filename) {
  const int fd = open_file(filename);
  const std::size_t length = file_size(fd);

  char *contents = static_cast<char *>(mmap(nullptr, length, PROT_READ, MAP_PRIVATE, fd, 0));

  return {
      .fd = fd,
      .position = 0,
      .length = length,
      .contents = contents,
  };
}

inline void munmap_file_from_disk(const MappedFile &mapped_file) {
  munmap(mapped_file.contents, mapped_file.length);
  close(mapped_file.fd);
}

inline void skip_spaces(MappedFile &mapped_file) {
  while (mapped_file.valid_position() && mapped_file.current() == ' ') {
    mapped_file.advance();
  }
}

inline void skip_nl(MappedFile &mapped_file) { mapped_file.advance(); }

template <typename Int> inline Int scan_int(MappedFile &mapped_file) {
  Int number = 0;
  while (mapped_file.valid_position() && std::isdigit(mapped_file.current())) {
    const int digit = mapped_file.current() - '0';
    number = number * 10 + digit;
    mapped_file.advance();
  }
  skip_spaces(mapped_file);
  return number;
}
} // namespace

Graph read_mmap_toker(const std::string &filename) {
  auto file = mmap_file_from_disk(filename);
  skip_spaces(file);

  // read header
  const ID n = scan_int<ID>(file);
  const ID m = 2 * scan_int<ID>(file);

  Graph graph;
  graph.nodes.resize(n + 1);
  graph.edges.resize(m);

  // read edges
  ID e = 0;
  for (ID u = 0; u < n; ++u) {
    skip_nl(file);
    skip_spaces(file);

    while (std::isdigit(file.current())) {
      graph.edges[e++] = scan_int<ID>(file) - 1;
    }
    graph.nodes[u + 1] = e;
  }

  munmap_file_from_disk(file);
  return graph;
}
} // namespace iobench