#include "writer/sstream_open_write.h"

#include <fcntl.h>
#include <unistd.h>

#include <sstream>

namespace iobench::sstream_open_write {
void write_graph(const Graph &graph, const std::string &filename) {
  std::stringstream ss;
  ss << graph.n() << ' ' << graph.m() / 2 << '\n';
  for (ID u = 0; u < graph.n(); ++u) {
    for (ID e = graph.nodes[u]; e < graph.nodes[u + 1]; ++e) {
      ss << graph.edges[e] + 1 << ' ';
    }
    ss << '\n';
  }

  const std::string str = ss.str();
  int fd = open(filename.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  write(fd, str.c_str(), str.length());
  close(fd);
}
} // namespace iobench::sstream_open_write
