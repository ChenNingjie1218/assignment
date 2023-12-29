#include <unistd.h>

#include <iostream>

#include "module.h"
class Module_1 : public Module {
 public:
  Module_1() = default;
  ~Module_1() = default;
  void Help() override {
    std::cout << "ID:" << ID_ << '\t' << "测试模块1" << std::endl;
  }
  int GetID() override { return ID_; }
  bool Work(Task& task) override {
    std::cout << "执行测试模块1..." << std::endl;
    return task.num1_ + task.num2_ == task.expect_;
  }

 private:
  const int ID_ = 1;
};

// 创建对象给用户使用
extern "C" Module* CreateObj() { return new Module_1(); }