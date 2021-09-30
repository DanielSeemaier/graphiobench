#include "writer/mybuf_open_write.h"

#include <fcntl.h>
#include <unistd.h>

#include <iostream>

namespace iobench::mybuf_open_write {
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
} // namespace

static constexpr int BUF_SIZE = 4 * 1024 * 1024; // 4 Mb
static constexpr int BUF_SIZE_LIMIT = BUF_SIZE - 1024;

void write_graph(const Graph &graph, const std::string &filename) {
  char buffer[BUF_SIZE];
  char *cur_buffer = buffer;

  int fd = open(filename.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

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
} // namespace iobench::mybuf_open_write
