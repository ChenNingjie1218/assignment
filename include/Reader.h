#ifndef READER_H
#define READER_H
#include <fcntl.h>
#include <unistd.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <istream>
#include <mutex>
#include <ostream>
#include <shared_mutex>

#include "MyPipe.h"
class Reader {
 public:
  static int block_;
  // static std::shared_mutex mutex_block_;
  static int dst_file_;
  Reader();
  ~Reader();
  void Work(MyPipe& r);

 private:
  void Write(const char* bufin, const std::streamsize& read_size);
  bool Read(MyPipe& r, std::streamsize& read_size, char* bufin);
  int w_block_;
};
#endif