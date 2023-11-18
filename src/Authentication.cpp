#include "authentication.h"
void sha256(const std::string& message, unsigned char* digest) {
  SHA256_CTX sha256Ctx;
  SHA256_Init(&sha256Ctx);
  SHA256_Update(&sha256Ctx, message.c_str(), message.length());
  SHA256_Final(digest, &sha256Ctx);
}