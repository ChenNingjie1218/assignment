#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

#include <iostream>

#include "authentication.h"
bool signMessage(const std::string& message, const std::string& privateKeyPath,
                 std::string& signature) {
  FILE* privateKeyFile = fopen(privateKeyPath.c_str(), "rb");
  if (!privateKeyFile) {
    std::cerr << "Failed to open private key file." << std::endl;
    return false;
  }

  RSA* rsaPrivateKey =
      PEM_read_RSAPrivateKey(privateKeyFile, nullptr, nullptr, nullptr);
  if (!rsaPrivateKey) {
    std::cerr << "Failed to parse private key." << std::endl;
    fclose(privateKeyFile);
    return false;
  }

  unsigned char sign[RSA_size(rsaPrivateKey)];
  unsigned int signLength = 0;

  int result = RSA_sign(NID_sha256,
                        reinterpret_cast<const unsigned char*>(message.c_str()),
                        message.length(), sign, &signLength, rsaPrivateKey);
  if (result != 1) {
    std::cerr << "Failed to sign the message." << std::endl;
    ERR_print_errors_fp(stderr);
    RSA_free(rsaPrivateKey);
    fclose(privateKeyFile);
    return false;
  }

  signature = std::string(reinterpret_cast<const char*>(sign), signLength);

  RSA_free(rsaPrivateKey);
  fclose(privateKeyFile);

  return true;
}

bool verifySignature(const std::string& message, const std::string& signature,
                     const std::string& publicKeyPath) {
  FILE* publicKeyFile = fopen(publicKeyPath.c_str(), "rb");
  if (!publicKeyFile) {
    std::cerr << "Failed to open public key file." << std::endl;
    return false;
  }

  RSA* rsaPublicKey =
      PEM_read_RSA_PUBKEY(publicKeyFile, nullptr, nullptr, nullptr);
  if (!rsaPublicKey) {
    std::cerr << "Failed to parse public key." << std::endl;
    fclose(publicKeyFile);
    return false;
  }

  int result = RSA_verify(
      NID_sha256, reinterpret_cast<const unsigned char*>(message.c_str()),
      message.length(),
      reinterpret_cast<const unsigned char*>(signature.c_str()),
      signature.length(), rsaPublicKey);
  if (result != 1) {
    std::cerr << "Failed to verify the signature." << std::endl;
    ERR_print_errors_fp(stderr);
    RSA_free(rsaPublicKey);
    fclose(publicKeyFile);
    return false;
  }

  std::cout << "Signature is valid." << std::endl;

  RSA_free(rsaPublicKey);
  fclose(publicKeyFile);

  return true;
}

int main() {
  std::string privateKeyPath = "private_key.pem";
  std::string publicKeyPath = "public_key.pem";
  std::string message = "Hello, world!";
  std::string signature;
  // 消息认证
  unsigned char digest[SHA256_DIGEST_LENGTH];
  // 计算SHA-256摘要
  sha256(message, digest);
  // 使用私钥对消息进行签名
  if (signMessage(std::string((char*)digest), privateKeyPath, signature)) {
    std::cout << "Message signature: " << signature << std::endl;

    // 使用公钥验证签名
    verifySignature(std::string((char*)digest), signature, publicKeyPath);
  }

  return 0;
}