#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

int main() {
  // 创建服务器套接字
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    std::cerr << "无法创建套接字" << std::endl;
    return -1;
  }

  // 准备服务器地址
  sockaddr_in serverAddress{};
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(8888);

  // 绑定套接字
  if (bind(serverSocket, (struct sockaddr *)&serverAddress,
           sizeof(serverAddress)) < 0) {
    std::cerr << "绑定失败" << std::endl;
    return -1;
  }

  // 监听连接
  if (listen(serverSocket, 3) < 0) {
    std::cerr << "监听失败" << std::endl;
    return -1;
  }

  std::cout << "等待客户端连接..." << std::endl;

  // 接受客户端连接
  int clientSocket;
  sockaddr_in clientAddress{};
  socklen_t clientAddressLength = sizeof(clientAddress);
  clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress,
                        &clientAddressLength);
  if (clientSocket < 0) {
    std::cerr << "接受连接失败" << std::endl;
    return -1;
  }

  std::cout << "客户端连接成功" << std::endl;

  // 从客户端接收数据
  char buffer[1024] = {0};
  int bytesRead = read(clientSocket, buffer, 1024);
  std::cout << "接收到的数据: " << buffer << std::endl;

  // 向客户端发送响应
  const char *response = "服务器已收到消息";
  write(clientSocket, response, strlen(response));

  // 关闭套接字
  close(clientSocket);
  close(serverSocket);

  return 0;
}