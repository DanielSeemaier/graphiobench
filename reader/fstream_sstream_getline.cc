#include "reader/fstream_sstream_getline.h"

#include <fstream>
#include <sstream>
#include <utility>

namespace iobench {
Graph read_fstream_sstream_getline(const std::string &filename) {
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
} // namespace iobench