#pragma once
#include "Listener.h"
#include "dataManager/DataManager.h"

class FTXListener : public Listener {
 public:
  FTXListener(DataManager &dataManager);

 protected:
  void passJSON(nlohmann::json json);
};
