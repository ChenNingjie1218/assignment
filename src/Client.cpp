#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

int main() {
  // 创建客户端套接字
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket == -1) {
    std::cerr << "无法创建套接字" << std::endl;
    return -1;
  }

  // 准备服务器地址
  sockaddr_in serverAddress{};
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(8888);

  // 将 IP 地址从字符串转换为网络地址
  if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
    std::cerr << "无效的地址/地址不支持" << std::endl;
    return -1;
  }

  // 连接到服务器
  if (connect(clientSocket, (struct sockaddr *)&serverAddress,
              sizeof(serverAddress)) < 0) {
    std::cerr << "连接失败" << std::endl;
    return -1;
  }

  // 发送数据到服务器
  const char *message = "你好，服务器";
  if (send(clientSocket, message, strlen(message), 0) < 0) {
    std::cerr << "发送失败" << std::endl;
    return -1;
  }

  // 接收服务器响应
  char buffer[1024] = {0};
  if (read(clientSocket, buffer, 1024) < 0) {
    std::cerr << "接收失败" << std::endl;
    return -1;
  }

  std::cout << "服务器响应: " << buffer << std::endl;

  // 关闭套接字
  close(clientSocket);

  return 0;
}