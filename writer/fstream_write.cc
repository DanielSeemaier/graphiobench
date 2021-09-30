#include "writer/fstream_write.h"

#include <fstream>

namespace iobench::fstream_write {
void write(const Graph &graph, const std::string &filename) {
  std::ofstream out(filename);

  const std::string header = std::to_string(graph.n()) + ' ' + std::to_string(graph.m() / 2) + '\n';
  out.write(header.c_str(), static_cast<std::streamsize>(header.length()));

  for (ID u = 0; u < graph.n(); ++u) {
    for (ID e = graph.nodes[u]; e < graph.nodes[u + 1]; ++e) {
      const ID v = graph.edges[e] + 1;
      const std::string str = std::to_string(v) + ' ';
      out.write(str.c_str(), static_cast<std::streamsize>(str.length()));
    }
    out.write("\n", 1);
  }
}
} // namespace iobench::fstream_write