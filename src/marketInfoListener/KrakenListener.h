#pragma once
#include "Listener.h"
#include "dataManager/DataManager.h"

class KrakenListener : public Listener {
 public:
  KrakenListener(DataManager &dataManager);

 protected:
  void passJSON(nlohmann::json json);
};
