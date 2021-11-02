#pragma once
#include "Listener.h"
#include "dataManager/DataManager.h"

class CoinbaseListener : public Listener {
 public:
  CoinbaseListener(DataManager &dataManager);

 protected:
  void passJSON(nlohmann::json json);
};
