#pragma once
#include "Listener.h"

class BitMEXListener : public Listener {
 public:
  BitMEXListener(OrderBook &orderBook);

 protected:
  void passJSON(nlohmann::json json);

 private:
  std::map<int, long> uniqueIdToPriceMap;
};
