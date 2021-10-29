#pragma once
#include "Listener.h"

class KrakenListener : public Listener {
 public:
  KrakenListener();

 protected:
  void passJSON(nlohmann::json json);
};
