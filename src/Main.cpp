#include <iostream>

#include "Copy.h"
int main() {
  std::cout << "请输入读者线程数量:" << std::endl;
  int NUM_THREAD;
  std::cin >> NUM_THREAD;
  Work(NUM_THREAD);
  return 0;
}