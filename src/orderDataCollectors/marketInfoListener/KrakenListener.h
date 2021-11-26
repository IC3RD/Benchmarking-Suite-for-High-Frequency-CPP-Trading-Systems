#pragma once

#include "Listener.h"

class KrakenListener : public Listener {
 public:
  KrakenListener(OrderBook &orderBook);

 protected:
  void passJSON(nlohmann::json json);
};
