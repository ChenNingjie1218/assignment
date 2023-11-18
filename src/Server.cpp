#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstddef>
#include <cstring>
#include <iostream>

#include "authentication.h"
#include "digital_signature.h"
#include "encryption.h"
#include "envolop.h"
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

  // unsigned char key[1024];
  // int bytesRead = read(clientSocket, key, 1024);
  // write(clientSocket, key, 1024);

  unsigned char buffer[1024];
  int bytesRead = read(clientSocket, buffer, 1024);
  // std::cout << "收到的字节数:" << bytesRead << std::endl;
  if (bytesRead >= 1024) {
    std::cerr << "太多了！！！！" << std::endl;
  }
  // 拆解消息
  std::string message((char *)buffer, bytesRead);
  size_t delimiter1 = 256;
  size_t delimiter2 = message.find("~", delimiter1 + 1);
  std::string encryptedKey = message.substr(0, delimiter1);
  std::string ciphertext = message.substr(delimiter1, delimiter2);
  std::string signature = message.substr(delimiter2 + 1);
  // 使用私钥解密密钥
  const char *privateKeyFile = "private_key_envolop.pem";
  std::string decryptedKey = decryptData(privateKeyFile, encryptedKey);
  // 使用解密的密钥解密密文
  unsigned char decrypted[1024];
  decrypt((unsigned char *)ciphertext.c_str(), 1024,
          (unsigned char *)decryptedKey.c_str(), decrypted);
  std::cout << "收到的消息：" << message << std::endl;
  std::cout << "解密出来的明文：" << decrypted << std::endl;

  // 数字认证
  unsigned char digest[SHA256_DIGEST_LENGTH];
  // 计算SHA-256摘要
  sha256(std::string((char *)decrypted), digest);
  // for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
  //   printf("%02x", digest[i]);
  // }
  // 验证数字签名
  std::string publicKeyPath = "public_key_signature.pem";
  verifySignature(std::string((char *)digest, SHA256_DIGEST_LENGTH), signature,
                  publicKeyPath);
  // 向客户端发送响应
  const char *response = "服务器已收到消息";
  write(clientSocket, response, strlen(response));
  // 关闭套接字
  close(clientSocket);
  close(serverSocket);

  return 0;
}