#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "authentication.h"
#include "digital_signature.h"
#include "encryption.h"
#include "envolop.h"
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

  // 要加密的明文
  std::string message;
  std::string plaintext = "NetSafety";
  int plaintextLength = plaintext.length();  // 减去结尾的空字符

  // --------------------- 生成密钥 ---------------------
  unsigned char key[32];
  size_t keyLength = sizeof(key);
  RAND_bytes(key, keyLength);

  // -----------------------   加密  ---------------------
  unsigned char ciphertext[plaintextLength];
  encrypt((unsigned char *)plaintext.c_str(), plaintextLength, key, ciphertext);

  // ----------------------- 消息认证 ---------------------
  unsigned char digest[SHA256_DIGEST_LENGTH];
  // 计算SHA-256摘要
  sha256(plaintext, digest);
  // for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
  //   printf("%02x", digest[i]);
  // }
  // ----------------------- 数字签名 ---------------------
  std::string privateKeyPath = "private_key_signature.pem";
  std::string signature;
  signMessage(std::string((char *)digest), privateKeyPath, signature);
  // ----------------------- 数字信封 ---------------------
  const char *publicKeyFile = "public_key_envolop.pem";
  // 加密密钥
  std::string encryptedData = encryptData(publicKeyFile, key, keyLength);

  message = encryptedData + (std::string((char *)ciphertext)) + "~" + signature;
  std::cout << "发送的明文是：" << plaintext << std::endl;
  std::cout << "发送的消息是：" << message << std::endl;
  //发送
  if (send(clientSocket, message.c_str(), message.length(), 0) < 0) {
    std::cerr << "发送失败" << std::endl;
    return -1;
  }
  // 接收服务器响应
  unsigned char buffer[1024] = {0};
  if (read(clientSocket, buffer, 1024) < 0) {
    std::cerr << "接收失败" << std::endl;
    return -1;
  }

  std::cout << "服务器响应: " << buffer << std::endl;

  // 关闭套接字
  close(clientSocket);

  return 0;
}