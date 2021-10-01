#include "writer/mybuf_open_write.h"

#include <fcntl.h>
#include <unistd.h>

namespace iobench {
namespace {
char *write_char(char *buffer, const char value) {
  *buffer = value;
  return buffer + 1;
}

template <typename Int> char *write_int(char *buffer, Int value) {
  static char rev_buffer[80];

  int pos = 0;
  do {
    rev_buffer[pos++] = value % 10;
    value /= 10;
  } while (value > 0);

  while (pos > 0) {
    *(buffer++) = '0' + rev_buffer[--pos];
  }

  return buffer;
}

template <int BUF_SIZE, int advice = -1> void write_mybuf_open_write(const Graph &graph, const std::string &filename) {
  constexpr int BUF_SIZE_LIMIT = BUF_SIZE - 1024;

  char buffer[BUF_SIZE];
  char *cur_buffer = buffer;

  int fd = open(filename.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  if (advice >= 0) {
    posix_fadvise(fd, 0, 0, advice);
  }

  auto flush_if_full = [&] {
    const std::size_t len = cur_buffer - buffer;
    if (len > BUF_SIZE_LIMIT) {
      write(fd, buffer, len);
      cur_buffer = buffer;
    }
  };

  cur_buffer = write_int(cur_buffer, graph.n());
  cur_buffer = write_char(cur_buffer, ' ');
  cur_buffer = write_int(cur_buffer, graph.m() / 2);
  cur_buffer = write_char(cur_buffer, '\n');

  for (ID u = 0; u < graph.n(); ++u) {
    for (ID e = graph.nodes[u]; e < graph.nodes[u + 1]; ++e) {
      const ID v = graph.edges[e] + 1;
      cur_buffer = write_int(cur_buffer, v);
      cur_buffer = write_char(cur_buffer, ' ');
      flush_if_full();
    }
    cur_buffer = write_char(cur_buffer, '\n');
  }

  write(fd, buffer, cur_buffer - buffer);
  close(fd);
}
} // namespace

void write_mybuf_open_write_16KB(const Graph &graph, const std::string &filename) {
  write_mybuf_open_write<16 * 1024>(graph, filename);
}

void write_mybuf_open_write_64KB(const Graph &graph, const std::string &filename) {
  write_mybuf_open_write<64 * 1024>(graph, filename);
}

void write_mybuf_open_write_1MB(const Graph &graph, const std::string &filename) {
  write_mybuf_open_write<1024 * 1024>(graph, filename);
}

void write_mybuf_open_write_4MB(const Graph &graph, const std::string &filename) {
  write_mybuf_open_write<4 * 1024 * 1024>(graph, filename);
}

void write_mybuf_open_write_4MB_fadvice(const Graph &graph, const std::string &filename) {
  write_mybuf_open_write<4 * 1024 * 1024, POSIX_FADV_SEQUENTIAL>(graph, filename);
}

void write_mybuf_open_write_16MB(const Graph &graph, const std::string &filename) {
  write_mybuf_open_write<16 * 1024 * 1024>(graph, filename);
}
} // namespace iobench
