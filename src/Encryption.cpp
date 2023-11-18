#include "encryption.h"

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
