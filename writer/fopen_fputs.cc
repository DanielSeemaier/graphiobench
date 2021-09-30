#include "writer/fopen_fputs.h"

#include <cstdio>

namespace iobench::fopen_fputs {
void write(const Graph &graph, const std::string &filename) {
  auto fd = std::fopen(filename.c_str(), "w");

  const std::string header = std::to_string(graph.n()) + ' ' + std::to_string(graph.m() / 2) + '\n';
  std::fputs(header.c_str(), fd);

  for (ID u = 0; u < graph.n(); ++u) {
    for (ID e = graph.nodes[u]; e < graph.nodes[u + 1]; ++e) {
      const ID v = graph.edges[e] + 1;
      const std::string str = std::to_string(v) + ' ';
      std::fputs(str.c_str(), fd);
    }
    std::fputs("\n", fd);
  }

  std::fclose(fd);
}

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

void write_my_itoa(const Graph &graph, const std::string &filename) {
  auto fd = std::fopen(filename.c_str(), "w");

  const std::string header = std::to_string(graph.n()) + ' ' + std::to_string(graph.m() / 2) + '\n';
  std::fputs(header.c_str(), fd);

  char itoa_buffer[80];

  for (ID u = 0; u < graph.n(); ++u) {
    for (ID e = graph.nodes[u]; e < graph.nodes[u + 1]; ++e) {
      const ID v = graph.edges[e] + 1;
      char *after_num = write_int(itoa_buffer, v);
      after_num = write_char(after_num, ' ');
      write_char(after_num, 0);
      std::fputs(itoa_buffer, fd);
    }
    std::fputs("\n", fd);
  }

  std::fclose(fd);
}
} // namespace iobench::fopen_fputs
