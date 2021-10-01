#pragma once

#include "graph.h"

#include <string>

namespace iobench {
Graph read_mmap_toker(const std::string &filename);
} // namespace iobench