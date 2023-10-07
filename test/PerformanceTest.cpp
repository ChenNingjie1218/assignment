#include <gtest/gtest.h>

#include <fstream>
#include <thread>
#include <vector>

#include "Copy.h"
const char* PATH_RESULT = "doc/PerformanceResult.txt";
const int NUM_THREAD = 10;

int main() {
  std::ofstream fw;
  fw.open(PATH_RESULT, std::ios::out);
  if (!fw) {
    std::cerr << "open file error!" << std::endl;
    exit(1);
  }
  for (int i = 1; i < NUM_THREAD; ++i) {
    auto start = std::chrono::high_resolution_clock::now();
    Work(i);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count();
    fw << duration << std::endl;
    Reader::block_ = 0;
  }

  return 0;
}