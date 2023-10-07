#include "MyPipe.h"
MyPipe::MyPipe() : is_over_(false) {
  if (pipe(fd) == -1) {
    std::cerr << "Failed to create the pipe" << std::endl;
    exit(1);
  }
}
MyPipe::~MyPipe() {}
void MyPipe::lock() { mutex_.lock(); }
void MyPipe::unlock() { mutex_.unlock(); }
int& MyPipe::Read() { return fd[0]; }
int& MyPipe::Write() { return fd[1]; }
std::shared_mutex& MyPipe::getMutex() { return mutex_; }
std::condition_variable& MyPipe::getCV(int type) {
  switch (type) {
    case 1:
      return cv_w_;
      break;
    case 2:
      return cv_r_;
      break;
    default:
      exit(1);
      break;
  }
}
bool MyPipe::isEmpty() {
  int bytesAvailable;
  ioctl(fd[0], FIONREAD, &bytesAvailable);
  return !bytesAvailable;
}

std::mutex& MyPipe::getMutexW() { return mutex_w_; }
std::mutex& MyPipe::getMutexR() { return mutex_r_; }
void MyPipe::Over() { is_over_ = true; }