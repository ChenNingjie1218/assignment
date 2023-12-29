#ifndef MODULE_H_
#define MODULE_H_
// 任务
typedef struct Task {
  Task(int num1, int num2, int expect)
      : num1_(num1), num2_(num2), expect_(expect) {}
  int num1_;
  int num2_;
  int expect_;
} Task;

// 基类
class Module {
 public:
  Module() = default;
  virtual ~Module() = default;
  virtual bool Work(Task &task) = 0;
  virtual int GetID() = 0;
  virtual void Help() = 0;
};

#endif