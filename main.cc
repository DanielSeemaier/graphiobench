#include <chrono>
#include <functional>
#include <iostream>
#include <string>

#include "fopen_fputs.h"
#include "fstream_sstream_getline.h"
#include "mmap_toker.h"
#include "use_graph.h"
#include "fopen_fwrite.h"

using namespace iobench;

constexpr static int WARMUP_REPS = 2;
constexpr static bool READ_BENCHMARK = false;
constexpr static int READ_REPS = 3;
constexpr static bool WRITE_BENCHMARK = true;
constexpr static int WRITE_REPS = 3;
constexpr static bool WRITE_BACK = false;

struct Reader {
  std::string name;
  std::function<Graph(const std::string &)> func;
};

struct Writer {
  std::string name;
  std::function<void(const Graph &, const std::string &)> func;
};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "usage: " << argv << " <graph>" << std::endl;
    std::exit(1);
  }
  const std::string filename = argv[1];

  if (READ_BENCHMARK) {
    std::vector<Reader> readers{{"fstream_sstream_getline", fstream_sstream_getline::read},
                                {"mmap_toker", mmap_toker::read}};

    std::cout << "Reading methods:" << std::endl;

    for (const auto &reader : readers) {
      if (WRITE_BACK) {
        Graph graph = reader.func(filename);
        fstream_sstream_getline::write(graph, filename + "." + reader.name);
      }

      // warmup reads
      for (int it = 0; it < WARMUP_REPS; ++it) {
        Graph graph = reader.func(filename);
        use_graph(graph);
      }

      // benchmark
      const auto begin = std::chrono::steady_clock::now();
      for (int it = 0; it < READ_REPS; ++it) {
        Graph graph = reader.func(filename);
        use_graph(graph);
      }
      const auto end = std::chrono::steady_clock::now();
      const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

      std::cout << "- " << reader.name << ": " << time << " ms" << std::endl;
    }
  }

  if (WRITE_BENCHMARK) {
    std::vector<Writer> writers{{"fstream_sstream_getline", fstream_sstream_getline::write},
                                {"fopen_fputs", fopen_fputs::write},
                                {"fopen_fwrite", fopen_fwrite::write}};

    const Graph graph = mmap_toker::read(filename);
    const std::string tmp_filename = "tmp.graph";

    std::cout << "Writing methods:" << std::endl;

    for (const auto &writer : writers) {
      // warmup reps
      for (int it = 0; it < WARMUP_REPS; ++it) {
        writer.func(graph, tmp_filename);
      }

      // benchmark
      const auto begin = std::chrono::steady_clock::now();
      for (int it = 0; it < WRITE_REPS; ++it) {
        writer.func(graph, tmp_filename);
      }
      const auto end = std::chrono::steady_clock::now();
      const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

      std::cout << "- " << writer.name << ": " << time << " ms" << std::endl;
    }
  }
}
