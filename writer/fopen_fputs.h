#pragma once

#include "graph.h"

#include <string>

namespace iobench::fopen_fputs {
void write(const Graph &graph, const std::string &filename);
void write_my_itoa(const Graph &graph, const std::string &filename);
}