#pragma once
#include "Listener.h"
//#include "../bollingerBand/MarketData.h"

class BitMEXListener : public Listener {
public:
  BitMEXListener();

protected:
  void passJSON(nlohmann::json json);

private:
  ix::WebSocket webSocket;
  // MarketData *data = nullptr;
};
