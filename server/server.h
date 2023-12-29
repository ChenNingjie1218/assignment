#ifndef SERVER_H_
#define SERVER_H_
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
class Server {
 public:
  Server() = delete;
  Server(int port, int length_of_queue_of_listen = 100,
         const char *str_bound_ip = NULL);
  virtual ~Server();
  void Run();

 protected:
  virtual void ServerFunction(int listen_socket) = 0;
  int port_;                       // 端口号
  int length_of_queue_of_listen_;  // 监听队列最大长度
  char *str_bound_ip_;             // 绑定的ip
};

class CenterServer : public Server {
 public:
  CenterServer(int port, int length_of_queue_of_listen = 100,
               const char *str_bound_ip = NULL);
  ~CenterServer() = default;

 protected:
  void ServerFunction(int listen_socket) override;
  void SendTestTask(const int &listen_socket);      // 下发任务
  void UpdateTestModule(const int &listen_socket);  // 更新测试模块
};
#endif