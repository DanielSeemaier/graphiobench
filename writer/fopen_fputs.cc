#include "writer/fopen_fputs.h"

#include <cstdio>

namespace iobench::fopen_fputs {
void write(const Graph &graph, const std::string &filename) {
  auto fd = std::fopen(filename.c_str(), "w");

  const std::string header = std::to_string(graph.n()) + " " + std::to_string(graph.m() / 2) + "\n";
  std::fputs(header.c_str(), fd);

  for (ID u = 0; u < graph.n(); ++u) {
    for (ID e = graph.nodes[u]; e < graph.nodes[u + 1]; ++e) {
      const ID v = graph.edges[e] + 1;
      const std::string str = std::to_string(v) + " ";
      std::fputs(str.c_str(), fd);
    }
    std::fputs("\n", fd);
  }

  std::fclose(fd);
}
} // namespace iobench::fopen_fputs
