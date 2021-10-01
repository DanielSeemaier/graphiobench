#pragma once

#include "graph.h"

#include <string>

namespace iobench {
void write_fstream_pipeout(const Graph &graph, const std::string &filename);
} // namespace iobench