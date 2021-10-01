#pragma once

#include "graph.h"

#include <string>

namespace iobench {
void write_fopen_fputs_to_string(const Graph &graph, const std::string &filename);
void write_fopen_fputs_my_itoa(const Graph &graph, const std::string &filename);
void write_fopen_fputs_my_itoa_largebuf(const Graph &graph, const std::string &filename);
void write_fopen_fputc_my_itoa_largebuf(const Graph &graph, const std::string &filename);
} // namespace iobench