#include <fcntl.h>
#include <gtest/gtest.h>
#include <openssl/md5.h>

#include <fstream>
#include <string>

// const std::string PATH_SRC = "testfle/";
// const std::string PATH_DST = "testfile/";
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

TEST(WRITE_AND_READ, 1G_is_correct) {
  std::string originalMD5 = calculateFileMD5("testfile/src1G");
  std::string dstMD5 = calculateFileMD5("testfile/dst1G");
  ASSERT_EQ(originalMD5, dstMD5);
}

TEST(WRITE_AND_READ, 2G_is_correct) {
  std::string originalMD5 = calculateFileMD5("testfile/src2G");
  std::string dstMD5 = calculateFileMD5("testfile/dst2G");
  ASSERT_EQ(originalMD5, dstMD5);
}

TEST(WRITE_AND_READ, 4G_is_correct) {
  std::string originalMD5 = calculateFileMD5("testfile/src4G");
  std::string dstMD5 = calculateFileMD5("testfile/dst4G");
  ASSERT_EQ(originalMD5, dstMD5);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}