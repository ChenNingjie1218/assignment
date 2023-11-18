#ifndef DIGITAL_SIGNATURE_H
#define DIGITAL_SIGNATURE_H
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

#include <iostream>
bool signMessage(const std::string& message, const std::string& privateKeyPath,
                 std::string& signature);
bool verifySignature(const std::string& message, const std::string& signature,
                     const std::string& publicKeyPath);
#endif