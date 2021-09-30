#pragma once

#include "graph.h"

#include <string>

namespace iobench::fstream_pipeout {
void write(const Graph &graph, const std::string &filename);
}