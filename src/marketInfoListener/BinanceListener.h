#pragma once
#include "Listener.h"
#include "dataManager/DataManager.h"

class BinanceListener : public Listener {
 public:
  BinanceListener(OrderBook &orderBook);

 protected:
  void passJSON(nlohmann::json json);

 private:
  int lastUpdated;
};
