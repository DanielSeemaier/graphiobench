#pragma once

#include "graph.h"

#include <string>

namespace iobench::mmap_toker {
Graph read(const std::string &filename);
} // namespace iobench::mmap_toker