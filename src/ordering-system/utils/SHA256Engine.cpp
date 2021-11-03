//
// Created by Jake Dickie on 20/10/2021.
//

#include "SHA256Engine.h"

#include <Poco/Crypto/DigestEngine.h>

// Call concrete constructor.
SHA256Engine::SHA256Engine() : DigestEngine("SHA256") {}
