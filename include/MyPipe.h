#ifndef MYPIPE_H
#define MYPIPE_H
#include <sys/ioctl.h>
#include <unistd.h>

#include <condition_variable>
#include <iostream>
#include <shared_mutex>
#define NDEBUG
class MyPipe {
 public:
  MyPipe();
  ~MyPipe();
  void lock();
  void unlock();
  int& Read();
  int& Write();
  std::shared_mutex& getMutex();
  std::condition_variable& getCV(int type);
  bool isEmpty();
  std::mutex& getMutexW();
  std::mutex& getMutexR();
  void Over();

 private:
  int fd[2];
  std::shared_mutex mutex_;
  std::condition_variable cv_r_;
  std::condition_variable cv_w_;
  std::mutex mutex_w_;
  std::mutex mutex_r_;
  bool is_over_;
};
#endif