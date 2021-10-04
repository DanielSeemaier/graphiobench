#include <chrono>
#include <functional>
#include <iostream>
#include <string>

#include "reader/fstream_sstream_getline.h"
#include "reader/mmap_toker.h"
#include "use_graph.h"
#include "writer/fopen_fprintf.h"
#include "writer/fopen_fputs.h"
#include "writer/fstream_pipeout.h"
#include "writer/fstream_write.h"
#include "writer/mybuf_open_write.h"
#include "writer/sstream_open_write.h"

using namespace iobench;

constexpr static int WARMUP_REPS = 2;
constexpr static bool READ_BENCHMARK = false;
constexpr static int READ_REPS = 5;
constexpr static bool WRITE_BENCHMARK = true;
constexpr static int WRITE_REPS = 5;
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
  if (argc < 2 && argc > 3) {
    std::cerr << "usage: " << argv << " <graph> [<output-dir='.'>]" << std::endl;
    std::exit(1);
  }
  const std::string filename = argv[1];
  const std::string output_dir = (argc >= 3) ? argv[2] : ".";

  if (READ_BENCHMARK) {
    std::vector<Reader> readers{{"fstream_sstream_getline", read_fstream_sstream_getline},
                                {"mmap_toker", read_mmap_toker}};

    std::cout << "Reading methods:" << std::endl;

    for (const auto &reader : readers) {
      if (WRITE_BACK) {
        Graph graph = reader.func(filename);
        write_mybuf_open_write_4MB(graph, filename + "." + reader.name);
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
      const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / READ_REPS;

      std::cout << "- " << reader.name << ": " << time << " ms" << std::endl;
    }
  }

  if (WRITE_BENCHMARK) {
    std::vector<Writer> writers{
        {"mybuf_open_write_16KB", write_mybuf_open_write_16KB},
        {"mybuf_open_write_4MB", write_mybuf_open_write_4MB},
        {"string_fstream_pipeout", write_graph_string},
        {"fopen_fputc_my_itoa_largebuf", write_fopen_fputc_my_itoa_largebuf},
        {"fopen_fputs_my_itoa_largebuf", write_fopen_fputs_my_itoa_largebuf},
        {"fopen_fputs_my_itoa", write_fopen_fputs_my_itoa},
        {"fopen_fputs_to_string", write_fopen_fputs_to_string},
        {"fstream_pipeout", write_fstream_pipeout},
        {"fopen_fprintf", write_fopen_fprintf},
        {"fstream_write", write_fstream_write},
        {"sstream_open_write", write_sstream_open_write},
    };

    const Graph graph = read_mmap_toker(filename);

    std::cout << "Writing methods:" << std::endl;

    for (const auto &writer : writers) {
      // warmup reps
      for (int it = 0; it < WARMUP_REPS; ++it) {
        const std::string out_filename = output_dir + "/" + writer.name + ".warmup." + std::to_string(it);
        writer.func(graph, out_filename);
      }

      // benchmark
      const auto begin = std::chrono::steady_clock::now();
      for (int it = 0; it < WRITE_REPS; ++it) {
        writer.func(graph, output_dir + "/" + writer.name + "." + std::to_string(it));
      }
      const auto end = std::chrono::steady_clock::now();
      const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / WRITE_REPS;

      std::cout << "- " << writer.name << ": " << time << " ms" << std::endl;
    }
  }
}
