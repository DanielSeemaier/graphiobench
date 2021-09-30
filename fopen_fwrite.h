#pragma once

#include "graph.h"

#include <string>

namespace iobench::fopen_fwrite {
void write(const Graph &graph, const std::string &filename);
}