//
// Created by Jake Dickie on 20/10/2021.
//

#include "SHA256Engine.h"
#include <Poco/Crypto/DigestEngine.h>

class SHA256Engine : public Poco::Crypto::DigestEngine
{
public:
    enum
    {
        BLOCK_SIZE = 64,
        DIGEST_SIZE = 32
    };

    SHA256Engine()
            : DigestEngine("SHA256")
    {


    }

};






