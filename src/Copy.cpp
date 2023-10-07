#include "Copy.h"

void Work(int num_thread) {
  MyPipe mypipe;
  std::thread t_writer([&]() {
    Writer w;
    w.Write(mypipe);
    return;
  });

  std::vector<std::thread> t_readers;
  for (int i = 0; i < num_thread; ++i) {
    t_readers.push_back(std::thread([&]() {
      Reader r;
      r.Work(mypipe);
      return;
    }));
  }
  mypipe.getCV(1).notify_one();
  t_writer.join();
  for (auto& t : t_readers) {
    t.join();
  }
  close(mypipe.Read());
  std::cout << "拷贝结束！" << std::endl;
}