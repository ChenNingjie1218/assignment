#include <unistd.h>

#include <iostream>

#include "module.h"
class Module_2 : public Module {
 public:
  Module_2() = default;
  ~Module_2() = default;
  void Help() override {
    std::cout << "ID:" << ID_ << '\t' << "测试模块2" << std::endl;
  }
  int GetID() override { return ID_; }
  bool Work(Task& task) override {
    std::cout << "执行测试模块2..." << std::endl;
    return task.num2_ * task.num2_ == task.expect_;
  }

 private:
  const int ID_ = 2;
};

// 创建对象给用户使用
extern "C" Module* CreateObj() { return new Module_2(); }