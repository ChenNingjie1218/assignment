#include <fcntl.h>
#include <gtest/gtest.h>
#include <openssl/md5.h>

#include <fstream>
#include <string>

#include "Copy.h"
#include "Writer.h"
const std::string PATH_SRC = "doc/srcFile";
const std::string PATH_DST = "doc/dstFile";
std::string calculateFileMD5(const std::string& filePath) {
  std::ifstream file(filePath, std::ios::binary);
  if (!file) {
    std::cerr << "Failed to open file: " << filePath << std::endl;
    return "";
  }

  MD5_CTX mdContext;
  MD5_Init(&mdContext);

  char buffer[4096];
  while (file.read(buffer, sizeof(buffer))) {
    MD5_Update(&mdContext, buffer, file.gcount());
  }

  unsigned char digest[MD5_DIGEST_LENGTH];
  MD5_Final(digest, &mdContext);

  std::ostringstream md5Stream;
  md5Stream << std::hex << std::setfill('0');
  for (const auto& byte : digest) {
    md5Stream << std::setw(2) << static_cast<unsigned int>(byte);
  }

  return md5Stream.str();
}

TEST(COPY, is_copy_correct) {
  for (int i = 1; i < 10; ++i) {
    Work(i);
    std::string originalMD5 = calculateFileMD5(PATH_SRC);
    std::string copiedMD5 = calculateFileMD5(PATH_DST);
    ASSERT_EQ(originalMD5, copiedMD5);
    Reader::block_ = 0;
  }
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}