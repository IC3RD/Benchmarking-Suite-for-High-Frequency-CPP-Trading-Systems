#include "SHA256Engine.h"

#include <Poco/Crypto/DigestEngine.h>
SHA256Engine::SHA256Engine() : DigestEngine("SHA256") {}
