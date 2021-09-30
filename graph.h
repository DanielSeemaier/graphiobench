#pragma once

#include <cstdint>
#include <vector>

namespace iobench {
using ID = std::uint32_t;

struct Graph {
  std::vector<ID> nodes;
  std::vector<ID> edges;

  [[nodiscard]] inline ID n() const { return nodes.size() - 1; }
  [[nodiscard]] inline ID m() const { return edges.size(); }
};
} // namespace iobench