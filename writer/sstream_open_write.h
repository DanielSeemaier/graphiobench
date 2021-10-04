#pragma once

#include "graph.h"

#include <string>

namespace iobench {
void write_sstream_open_write(const Graph &graph, const std::string &filename);
void write_graph_string(const Graph &graph, const std::string &filename);
} // namespace iobench