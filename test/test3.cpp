#include <openssl/sha.h>

#include <cstring>
#include <iostream>

void sha256(const std::string& message, unsigned char* digest) {
  SHA256_CTX sha256Ctx;
  SHA256_Init(&sha256Ctx);
  SHA256_Update(&sha256Ctx, message.c_str(), message.length());
  SHA256_Final(digest, &sha256Ctx);
}

int main() {
  std::string message = "Hello, world!";
  unsigned char digest[SHA256_DIGEST_LENGTH];

  // 计算SHA-256摘要
  sha256(message, digest);

  // 打印摘要结果
  std::cout << "SHA-256 Digest: ";
  for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
    printf("%02x", digest[i]);
  }
  std::cout << std::endl;

  return 0;
}