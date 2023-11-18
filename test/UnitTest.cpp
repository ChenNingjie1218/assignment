#include <gtest/gtest.h>
#include <openssl/rand.h>

#include "authentication.h"
#include "digital_signature.h"
#include "encryption.h"
#include "envolop.h"

TEST(ENCRYPTION, test_encrypt) {
  // 要加密的明文
  unsigned char plaintext[] = "Hello World!";
  int plaintextLength = sizeof(plaintext) - 1;  // 减去结尾的空字符
                                                // 生成密钥
  unsigned char key[32];
  RAND_bytes(key, sizeof(key));
  // 加密
  unsigned char ciphertext[plaintextLength];
  encrypt(plaintext, plaintextLength, key, ciphertext);

  // 解密
  unsigned char decrypted[plaintextLength];
  decrypt(ciphertext, plaintextLength, key, decrypted);

  // 输出结果
  // std::cout << "明文: " << plaintext << std::endl;
  // std::cout << "密文: ";
  // for (int i = 0; i < plaintextLength; ++i)
  //   std::cout << std::hex << (int)ciphertext[i];
  // std::cout << std::endl;
  // std::cout << "解密后的数据: " << decrypted << std::endl;
  ASSERT_EQ(std::string((char*)plaintext, plaintextLength),
            std::string((char*)decrypted, plaintextLength));
};

TEST(SIGNATURE, test_signature) {
  std::string privateKeyPath = "private_key_signature.pem";
  std::string publicKeyPath = "public_key_signature.pem";
  std::string message = "Hello, world!";
  std::string signature;
  // 消息认证
  unsigned char digest[SHA256_DIGEST_LENGTH];
  // 计算SHA-256摘要
  sha256(message, digest);
  // 使用私钥对消息进行签名
  if (signMessage(std::string((char*)digest), privateKeyPath, signature)) {
    // std::cout << "Message signature: " << signature << std::endl;

    // 使用公钥验证签名
    ASSERT_EQ(
        verifySignature(std::string((char*)digest), signature, publicKeyPath),
        true);
  }
};

TEST(ENVOLOP, test_envolop) {
  // 假设已经有私钥和公钥文件
  const char* privateKeyFile = "private_key_envolop.pem";
  const char* publicKeyFile = "public_key_envolop.pem";

  // 要加密的数据
  unsigned char key[32];
  RAND_bytes(key, sizeof(key));
  size_t inputLength = sizeof(key);

  // 加密数据
  std::string encryptedData = encryptData(publicKeyFile, key, inputLength);
  if (!encryptedData.empty()) {
    // std::cout << "加密后的数据：" << encryptedData << std::endl;
  }

  // 解密数据
  std::string decryptedData = decryptData(privateKeyFile, encryptedData);
  if (!decryptedData.empty()) {
    std::string s_key((char*)key, inputLength);
    // std::cout << "加密前的数据：" << s_key << std::endl;
    // std::cout << "解密后的数据：" << decryptedData << std::endl;
    ASSERT_EQ(s_key, decryptedData);
  }
}
int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}