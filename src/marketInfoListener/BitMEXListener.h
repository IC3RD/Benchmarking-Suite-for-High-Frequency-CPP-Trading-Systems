#pragma once
#include "Listener.h"
#include "dataManager/DataManager.h"
//#include "../bollingerBand/MarketData.h"

class BitMEXListener : public Listener {
 public:
  BitMEXListener(DataManager &dataManager);

 protected:
  void passJSON(nlohmann::json json);

 private:
  ix::WebSocket webSocket;
  // MarketData *data = nullptr;
};
