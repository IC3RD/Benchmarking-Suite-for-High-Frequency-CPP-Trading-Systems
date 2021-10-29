#pragma once
#include "Listener.h"

class BinanceListener: public Listener {
public:
    BinanceListener();
protected:
    void passJSON(nlohmann::json json);
};
