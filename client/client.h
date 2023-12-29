#ifndef CLIENT_H_
#define CLIENT_H_
#include <arpa/inet.h>
#include <dlfcn.h>
#include <memory.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "module.h"

// 状态
typedef struct Status {
  char status_[100] = {0};          // 记录当前状态
  char version_[100] = {0};         // 插件版本号
  int finished_;                    // 完成了多少进度
  int sum_;                         // 任务总数
  bool result[10000000] = {false};  // 假设最多100w任务
} Status;

class Client {
 public:
  Client() = delete;
  Client(int serverport, const char* str_server_ip);
  virtual ~Client();
  void Run();

 protected:
  virtual void ClientFunction(int connected_socket) = 0;
  int serverport_;
  const char* str_server_ip_;
};

class TestClient : public Client {
 public:
  TestClient(int serverport, const char* str_server_ip);
  ~TestClient() = default;

 protected:
  void ClientFunction(int connected_socket) override;
  void RecvTestTask(const int& listen_socket, Status* sharedStatus,
                    std::vector<Task>& tasks);  // 下发任务
  void ExecuteTasks(Status* sharedStatus,
                    std::vector<Task>& tasks);  // 执行任务
  void UpdateTestModule(const int& listen_socket,
                        Status* sharedStatus);    // 更新测试模块
  void SerializeTasks(std::vector<Task>& tasks);  // 序列化任务
};

#endif