#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>

#include <iostream>
#include <string>

std::string encryptMessage(const std::string& message, const std::string& key);

#endif