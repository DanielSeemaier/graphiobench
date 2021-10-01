#pragma once

#include "graph.h"

#include <string>

namespace iobench {
Graph read_fstream_sstream_getline(const std::string &filename);
} // namespace iobench