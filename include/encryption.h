#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <openssl/aes.h>
#include <openssl/rand.h>

#include <iostream>
void encrypt(const unsigned char* plaintext, int plaintextLength,
             const unsigned char* key, unsigned char* ciphertext);
void decrypt(const unsigned char* ciphertext, int ciphertextLength,
             const unsigned char* key, unsigned char* decrypted);
#endif