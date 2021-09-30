#pragma once

#include "graph.h"

#include <string>

namespace iobench::fstream_sstream_getline {
Graph read(const std::string &filename);
void write(const Graph &graph, const std::string &filename);
} // namespace iobench::fstream_sstream_getline