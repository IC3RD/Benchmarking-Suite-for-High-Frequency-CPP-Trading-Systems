#include "CoinbaseListener.h"

#include <iomanip>
#include <iostream>
#include <json/single_include/nlohmann/json.hpp>
#include <string>

CoinbaseListener::CoinbaseListener(DataManager &dataManager)
    : Listener("wss://ws-feed.exchange.coinbase.com",
               "{\"type\": \"subscribe\", \"product_ids\": [\"BTC-USD\"], "
               "\"channels\": [\"ticker\"]}",
               "COINBASE", dataManager) {}

// reference: just looking at the printing json, the dictionary's keys are very
// explict :)
void CoinbaseListener::passJSON(nlohmann::json json) {
  if (json.contains("best_ask")) {
    std::string askPrice = json.at("best_ask");
  }
  if (json.contains("best_bid")) {
    std::string bidPrice = json.at("best_bid");
  }
  // current volume is not obvious here, only gives 24hr volume
}
