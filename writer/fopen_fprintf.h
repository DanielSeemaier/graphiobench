#pragma once

#include "graph.h"

#include <string>

namespace iobench {
void write_fopen_fprintf(const Graph &graph, const std::string &filename);
} // namespace iobench