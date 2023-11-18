#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
#include <openssl/sha.h>

#include <cstring>
#include <iostream>

void sha256(const std::string& message, unsigned char* digest);
#endif