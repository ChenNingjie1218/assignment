#include "digital_signature.h"
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