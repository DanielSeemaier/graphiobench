#include "writer/fstream_pipeout.h"

#include <fstream>

namespace iobench::fstream_pipeout {
void write(const Graph &graph, const std::string &filename) {
  std::ofstream out(filename, std::ios_base::out);
  out << graph.n() << ' ' << graph.m() / 2 << '\n';
  for (ID u = 0; u < graph.n(); ++u) {
    for (ID e = graph.nodes[u]; e < graph.nodes[u + 1]; ++e) {
      out << graph.edges[e] + 1 << ' ';
    }
    out << '\n';
  }
}
} // namespace iobench::fstream_pipeout