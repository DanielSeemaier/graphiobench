#include "writer/fopen_fputs.h"

#include <cstdio>

namespace iobench::fopen_fputs {
void write_graph_to_string(const Graph &graph, const std::string &filename) {
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

template <typename Int> void write_int_to_file(FILE *fd, Int value) {
  static char rev_buffer[80];

  int pos = 0;
  do {
    rev_buffer[pos++] = value % 10;
    value /= 10;
  } while (value > 0);

  while (pos > 0) {
    fputc('0' + rev_buffer[--pos], fd);
  }
}
} // namespace

void write_graph_my_itoa(const Graph &graph, const std::string &filename) {
  auto fd = std::fopen(filename.c_str(), "w");

  char buffer[80];

  // header
  *write_int(buffer, graph.n()) = 0;
  std::fputs(buffer, fd);
  std::fputs(" ", fd);
  *write_int(buffer, graph.m() / 2) = 0;
  std::fputs(buffer, fd);
  std::fputs("\n", fd);

  // body
  for (ID u = 0; u < graph.n(); ++u) {
    for (ID e = graph.nodes[u]; e < graph.nodes[u + 1]; ++e) {
      *write_char(write_int(buffer, graph.edges[e] + 1), ' ') = 0;
      std::fputs(buffer, fd);
    }
    std::fputs("\n", fd);
  }

  std::fclose(fd);
}

void write_graph_my_itoa_largebuf(const Graph &graph, const std::string &filename) {
  auto fd = std::fopen(filename.c_str(), "w");

  constexpr std::size_t BUF_SIZE = 1024 * 1024 * 4; // 4 Mb
  char large_buf[BUF_SIZE];
  std::setvbuf(fd, large_buf, _IOFBF, BUF_SIZE);

  char buffer[80];

  // header
  *write_int(buffer, graph.n()) = 0;
  std::fputs(buffer, fd);
  std::fputs(" ", fd);
  *write_int(buffer, graph.m() / 2) = 0;
  std::fputs(buffer, fd);
  std::fputs("\n", fd);

  // body
  for (ID u = 0; u < graph.n(); ++u) {
    for (ID e = graph.nodes[u]; e < graph.nodes[u + 1]; ++e) {
      *write_char(write_int(buffer, graph.edges[e] + 1), ' ') = 0;
      std::fputs(buffer, fd);
    }
    std::fputs("\n", fd);
  }

  std::fclose(fd);
}

void write_graph_my_itoa_largebuf_direct(const Graph &graph, const std::string &filename) {
  auto fd = std::fopen(filename.c_str(), "w");

  constexpr std::size_t BUF_SIZE = 1024 * 1024 * 4; // 4 Mb
  char large_buf[BUF_SIZE];
  std::setvbuf(fd, large_buf, _IOFBF, BUF_SIZE);

  // header
  write_int_to_file(fd, graph.n());
  std::fputc(' ', fd);
  write_int_to_file(fd, graph.m() / 2);
  std::fputc('\n', fd);

  // body
  for (ID u = 0; u < graph.n(); ++u) {
    for (ID e = graph.nodes[u]; e < graph.nodes[u + 1]; ++e) {
      write_int_to_file(fd, graph.edges[e] + 1);
      std::fputc(' ', fd);
    }
    std::fputc('\n', fd);
  }

  std::fclose(fd);
}
} // namespace iobench::fopen_fputs
