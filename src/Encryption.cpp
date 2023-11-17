#include <openssl/aes.h>
#include <openssl/rand.h>

#include <cstring>
#include <iostream>

std::string encryptMessage(const std::string& message, const std::string& key) {
  const int keyLength = 128;  // 128-bit key
  unsigned char iv[AES_BLOCK_SIZE];
  unsigned char aesKey[keyLength / 8];

  // Generate a random IV (Initialization Vector)
  RAND_bytes(iv, sizeof(iv));

  // Convert string key to byte array
  memcpy(aesKey, key.c_str(), keyLength / 8);

  // Encrypt
  AES_KEY encryptKey;
  AES_set_encrypt_key(aesKey, keyLength, &encryptKey);

  int encryptedLength =
      ((message.length() + AES_BLOCK_SIZE) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
  unsigned char encrypted[encryptedLength];
  AES_cbc_encrypt((const unsigned char*)message.c_str(), encrypted,
                  message.length(), &encryptKey, iv, AES_ENCRYPT);

  // Combine IV and ciphertext
  std::string encodedIV(reinterpret_cast<char*>(iv), AES_BLOCK_SIZE);
  std::string ciphertext(reinterpret_cast<char*>(encrypted), encryptedLength);

  return encodedIV + ciphertext;
}