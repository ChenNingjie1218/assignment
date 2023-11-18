#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>

#include <iostream>

// 加密数据
std::string encryptData(const char* publicKeyFile,
                        const unsigned char* inputData, size_t inputLength) {
  std::string encryptedData;

  // 打开公钥文件
  FILE* publicKeyFilePtr = fopen(publicKeyFile, "rb");
  if (!publicKeyFilePtr) {
    std::cerr << "无法打开公钥文件" << std::endl;
    return encryptedData;
  }

  // 从公钥文件中加载RSA结构
  RSA* rsa = RSA_new();
  rsa = PEM_read_RSA_PUBKEY(publicKeyFilePtr, &rsa, nullptr, nullptr);

  // 计算密文长度
  size_t encryptedLength = RSA_size(rsa);
  unsigned char* encryptedBuffer = new unsigned char[encryptedLength];

  // 加密数据
  int result = RSA_public_encrypt(inputLength, inputData, encryptedBuffer, rsa,
                                  RSA_PKCS1_PADDING);
  if (result == -1) {
    std::cerr << "加密数据时发生错误" << std::endl;
    ERR_print_errors_fp(stderr);
  } else {
    // 将加密后的数据保存为字符串
    encryptedData.assign(reinterpret_cast<const char*>(encryptedBuffer),
                         result);
  }

  // 释放资源
  RSA_free(rsa);
  fclose(publicKeyFilePtr);
  delete[] encryptedBuffer;

  return encryptedData;
}

// 解密数据
std::string decryptData(const char* privateKeyFile,
                        const std::string& encryptedData) {
  std::string decryptedData;

  // 打开私钥文件
  FILE* privateKeyFilePtr = fopen(privateKeyFile, "rb");
  if (!privateKeyFilePtr) {
    std::cerr << "无法打开私钥文件" << std::endl;
    return decryptedData;
  }

  // 从私钥文件中加载RSA结构
  RSA* rsa = RSA_new();
  rsa = PEM_read_RSAPrivateKey(privateKeyFilePtr, &rsa, nullptr, nullptr);

  // 计算明文长度
  size_t decryptedLength = RSA_size(rsa);
  unsigned char* decryptedBuffer = new unsigned char[decryptedLength];

  // 解密数据
  int result = RSA_private_decrypt(
      encryptedData.length(),
      reinterpret_cast<const unsigned char*>(encryptedData.c_str()),
      decryptedBuffer, rsa, RSA_PKCS1_PADDING);
  if (result == -1) {
    std::cerr << "解密数据时发生错误" << std::endl;
    ERR_print_errors_fp(stderr);
  } else {
    // 将解密后的数据保存为字符串
    decryptedData.assign(reinterpret_cast<const char*>(decryptedBuffer),
                         result);
  }

  // 释放资源
  RSA_free(rsa);
  fclose(privateKeyFilePtr);
  delete[] decryptedBuffer;

  return decryptedData;
}

int main() {
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
    std::cout << "加密后的数据：" << encryptedData << std::endl;
  }

  // 解密数据
  std::string decryptedData = decryptData(privateKeyFile, encryptedData);
  if (!decryptedData.empty()) {
    std::cout << "加密前的数据：" << key << std::endl;
    std::cout << "解密后的数据：" << decryptedData << std::endl;
  }

  return 0;
}