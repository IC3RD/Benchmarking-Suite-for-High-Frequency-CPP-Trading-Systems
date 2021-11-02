//
// Created by Jake Dickie on 20/10/2021.
//

#ifndef CPPDESIGNPATTERNSLOWLATENCY_SHA256ENGINE_H
#define CPPDESIGNPATTERNSLOWLATENCY_SHA256ENGINE_H

#include <Poco/Crypto/DigestEngine.h>
#include <string>

class SHA256Engine : public Poco::Crypto::DigestEngine {
public:
  enum { BLOCK_SIZE = 64, DIGEST_SIZE = 32 };

  SHA256Engine();
};

#endif // CPPDESIGNPATTERNSLOWLATENCY_SHA256ENGINE_H
