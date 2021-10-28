//
// Created by Jake Dickie on 20/10/2021.
//
#pragma once
#include <Poco/Crypto/DigestEngine.h>

#include <string>

class SHA256Engine : public Poco::Crypto::DigestEngine {
 public:
  enum { BLOCK_SIZE = 64, DIGEST_SIZE = 32 };

  SHA256Engine();
};