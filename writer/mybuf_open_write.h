#pragma once

#include "graph.h"

#include <string>

namespace iobench {
void write_mybuf_open_write_16KB(const Graph &graph, const std::string &filename);
void write_mybuf_open_write_64KB(const Graph &graph, const std::string &filename);
void write_mybuf_open_write_1MB(const Graph &graph, const std::string &filename);
void write_mybuf_open_write_4MB(const Graph &graph, const std::string &filename);
void write_mybuf_open_write_4MB_fadvice(const Graph &graph, const std::string &filename);
void write_mybuf_open_write_16MB(const Graph &graph, const std::string &filename);
} // namespace iobench