#pragma once

#include "graph.h"

#include <string>

namespace iobench {
void write_fstream_write(const Graph &graph, const std::string &filename);
} // namespace iobench