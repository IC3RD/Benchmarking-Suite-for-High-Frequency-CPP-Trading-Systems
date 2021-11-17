#pragma once
#include "Listener.h"
#include "dataManager/DataManager.h"

class KrakenListener : public Listener {
 public:
  KrakenListener(OrderBook &orderBook);

 protected:
  void passJSON(nlohmann::json json);
};
