#pragma once

#include "graph.h"

#include <string>

namespace iobench {
void write_mybuf_open_write(const Graph &graph, const std::string &filename);
} // namespace iobench