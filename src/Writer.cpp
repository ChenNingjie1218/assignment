#include "Writer.h"

const std::streamsize BUFFER_SIZE = 64 * 1024;
const char* PATH_SRC = "doc/srcFile";

Writer::Writer() {
  src_file_.open(PATH_SRC, std::ios::in | std::ios::binary);
  if (!src_file_) {
    std::cerr << "open source file failed!" << std::endl;
    exit(1);
  }
}

Writer::~Writer() {
  if (src_file_.is_open()) {
    src_file_.close();
  } else {
    std::cerr << "写者析构的时候，源文件没被打开" << std::endl;
    exit(1);
  }
}
void Writer::Write(MyPipe& w) {
  // std::streamsize BUFFER_SIZE = sysconf(w.Write());
#ifndef NDEBUG
  std::cout << "BUFFER_SIZE is " << BUFFER_SIZE << std::endl;
#endif
  char bufout[BUFFER_SIZE];
  while (src_file_.read(bufout, BUFFER_SIZE)) {
    std::streamsize read_size = src_file_.gcount();
    std::unique_lock<std::mutex> cv_lock(w.getMutexW());
    // while (!w.isEmpty()) {
#ifndef NDEBUG
    std::cout << "写者等待管道空" << std::endl;
#endif
    w.getCV(1).wait(cv_lock, [&] { return w.isEmpty(); });
    // }
#ifndef NDEBUG
    std::cout << "写者准备向管道写入" << read_size << std::endl;
#endif
    std::unique_lock<std::shared_mutex> w_lock(w.getMutex());
    std::streamsize write_size = write(w.Write(), bufout, read_size);
#ifndef NDEBUG
    std::cout << "写者向管道写入" << write_size << std::endl;
#endif
    if (write_size == -1) {
      std::cerr << "can not write to pipe!" << std::endl;
      exit(1);
    }
    w.getCV(2).notify_all();
  }
#ifndef NDEBUG
  std::cout << "写者线程操作结束" << std::endl;
#endif
  close(w.Write());
  w.Over();
  w.getCV(2).notify_all();
}