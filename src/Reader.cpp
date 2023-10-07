#include "Reader.h"

#include <chrono>

// const std::streamsize BUFFER_SIZE = 4 * 1024 * 1024;
const std::streamsize BUFFER_SIZE = 16 * 1024;
const char* PATH_DST = "doc/dstFile";
int Reader::block_ = 0;
// std::shared_mutex Reader::mutex_block_;
int Reader::dst_file_ = open(PATH_DST, O_WRONLY | O_CREAT | O_TRUNC, 0664);

Reader::Reader() {}

Reader::~Reader() {}

bool Reader::Read(MyPipe& r, std::streamsize& read_size, char* bufin) {
  std::unique_lock<std::mutex> cv_lock(r.getMutexR());
  // while (r.isEmpty()) {
#ifndef NDEBUG
  std::cout << "读者等待管道满" << std::endl;
#endif
  r.getCV(2).wait_for(cv_lock, std::chrono::seconds(1),
                      [&] { return !r.isEmpty(); });
  // }
#ifndef NDEBUG
  std::cout << "读线程准备从管道读" << std::endl;
#endif
  std::unique_lock<std::shared_mutex> r_lock(r.getMutex());
  read_size = read(r.Read(), bufin, BUFFER_SIZE);
#ifndef NDEBUG
  std::cout << "读线程从管道读read_size:" << read_size << std::endl;
#endif
  w_block_ = block_++;
  r.getCV(1).notify_one();
  return read_size > 0;
}

void Reader::Work(MyPipe& r) {
  char bufin[BUFFER_SIZE];
  std::streamsize read_size;
  while (Read(r, read_size, bufin)) {
    Write(bufin, read_size);
  }
#ifndef NDEBUG
  std::cout << "读者线程操作结束" << std::endl;
#endif
}

void Reader::Write(const char* bufin, const std::streamsize& read_size) {
  pwrite(dst_file_, bufin, read_size, w_block_ * BUFFER_SIZE);
}