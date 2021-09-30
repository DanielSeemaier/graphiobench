#include "fstream_sstream_getline.h"

#include <fstream>
#include <sstream>
#include <utility>

namespace iobench::fstream_sstream_getline {
Graph read(const std::string &filename) {
  std::ifstream in(filename);

  // read n, m
  const auto [n, m] = [&in] {
    std::string line;
    std::getline(in, line);
    ID _n, _m;
    std::stringstream(line) >> _n >> _m;
    return std::pair{_n, 2 * _m};
  }();

  Graph graph;
  graph.nodes.resize(n + 1);
  graph.edges.resize(m);

  ID e = 0;
  for (ID u = 0; u < n; ++u) {
    std::string line;
    std::getline(in, line);
    std::stringstream ss(line);

    for (ID id; ss >> id;) {
      graph.edges[e++] = id - 1;
    }
    graph.nodes[u + 1] = e;
  }

  return graph;
}

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
} // namespace iobench::fstream_sstream_getline