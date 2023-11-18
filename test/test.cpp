#include <openssl/aes.h>
#include <openssl/rand.h>

#include <iostream>

void encrypt(const unsigned char* plaintext, int plaintextLength,
             const unsigned char* key, unsigned char* ciphertext) {
  AES_KEY aesKey;
  AES_set_encrypt_key(key, 256, &aesKey);
  AES_encrypt(plaintext, ciphertext, &aesKey);
}

void decrypt(const unsigned char* ciphertext, int ciphertextLength,
             const unsigned char* key, unsigned char* decrypted) {
  AES_KEY aesKey;
  AES_set_decrypt_key(key, 256, &aesKey);
  AES_decrypt(ciphertext, decrypted, &aesKey);
}

int main() {
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
  std::cout << "明文: " << plaintext << std::endl;
  std::cout << "密文: ";
  for (int i = 0; i < plaintextLength; ++i)
    std::cout << std::hex << (int)ciphertext[i];
  std::cout << std::endl;
  std::cout << "解密后的数据: " << decrypted << std::endl;

  return 0;
}