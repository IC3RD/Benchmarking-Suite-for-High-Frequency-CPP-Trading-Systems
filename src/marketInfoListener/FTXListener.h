#pragma once
#include "Listener.h"

class FTXListener : public Listener {
 public:
  FTXListener();

 protected:
  void passJSON(nlohmann::json json);
};
