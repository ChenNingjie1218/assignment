#ifndef WRITER_H
#define WRITER_H
#include <unistd.h>

#include <fstream>
#include <ios>
#include <iostream>
#include <mutex>

#include "MyPipe.h"
class Writer {
 public:
  Writer();
  ~Writer();
  void Write(MyPipe& w);

 private:
  std::ifstream src_file_;
};
#endif