#pragma once

#include "graph.h"

#include <string>

namespace iobench::sstream_open_write {
void write_graph(const Graph &graph, const std::string &filename);
} // namespace iobench::sstream_open_write