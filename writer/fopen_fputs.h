#pragma once

#include "graph.h"

#include <string>

namespace iobench::fopen_fputs {
void write_graph_to_string(const Graph &graph, const std::string &filename);
void write_graph_my_itoa(const Graph &graph, const std::string &filename);
void write_graph_my_itoa_largebuf(const Graph &graph, const std::string &filename);
void write_graph_my_itoa_largebuf_direct(const Graph &graph, const std::string &filename);
}