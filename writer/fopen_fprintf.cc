#include "writer/fopen_fprintf.h"

#include <cstdio>

namespace iobench {
void write_fopen_fprintf(const Graph &graph, const std::string &filename) {
  auto fd = std::fopen(filename.c_str(), "w");

  std::fprintf(fd, "%d %d\n", graph.n(), graph.m() / 2);

  for (ID u = 0; u < graph.n(); ++u) {
    for (ID e = graph.nodes[u]; e < graph.nodes[u + 1]; ++e) {
      std::fprintf(fd, "%d ", graph.edges[e] + 1);
    }
    std::fprintf(fd, "\n");
  }

  std::fclose(fd);
}
} // namespace iobench
