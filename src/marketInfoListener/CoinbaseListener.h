#pragma once
#include "Listener.h"

class CoinbaseListener: public Listener {
public:
    CoinbaseListener();
protected:
    void passJSON(nlohmann::json json);
};
