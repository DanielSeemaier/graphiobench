#pragma once

#include "graph.h"

#include <string>

namespace iobench::fstream_write {
void write(const Graph &graph, const std::string &filename);
}