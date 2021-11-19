#pragma once

#include <Poco/Crypto/DigestEngine.h>

class SHA256Engine : public Poco::Crypto::DigestEngine {
 public:
  enum { BLOCK_SIZE = 64, DIGEST_SIZE = 32 };

  SHA256Engine();
};
