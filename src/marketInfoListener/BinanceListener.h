#pragma once
#include "Listener.h"
#include "dataManager/DataManager.h"

class BinanceListener : public Listener {
 public:
  BinanceListener(DataManager &dataManager);

 protected:
  void passJSON(nlohmann::json json);
};
