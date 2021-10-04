#pragma once

#include "graph.h"

#include <string>

namespace iobench {
void write_graph_sstream(const Graph &graph, const std::string &filename);
void write_graph_string(const Graph &graph, const std::string &filename);
} // namespace iobench