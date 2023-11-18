#ifndef ENVOLOP_H
#define ENVOLOP_H
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

#include <iostream>

// 加密数据
std::string encryptData(const char* publicKeyFile,
                        const unsigned char* inputData, size_t inputLength);
// 解密数据
std::string decryptData(const char* privateKeyFile,
                        const std::string& encryptedData);
#endif