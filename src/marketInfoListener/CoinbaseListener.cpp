#include "CoinbaseListener.h"

#include <iomanip>
#include <iostream>
#include <json/single_include/nlohmann/json.hpp>
#include <string>

CoinbaseListener::CoinbaseListener(DataManager &dataManager)
    : Listener("wss://ws-feed.exchange.coinbase.com",
               "{\"type\": \"subscribe\", \"product_ids\": [\"BTC-USD\"], "
               "\"channels\": [\"ticker\"]}",
               Exchange::COINBASE, dataManager) {}

// reference: just looking at the printing json, the dictionary's keys are very
// explict :)
void CoinbaseListener::passJSON(nlohmann::json json) {
  int askPrice = -1;
  int bidPrice = -1;
  int askVolume = -1;
  int bidVolume = -1;
  if (json.contains("best_ask")) {
    std::string val = json.at("best_ask");
    askPrice = std::stoi(val);
  }
  if (json.contains("best_bid")) {
    std::string val = json.at("best_bid");
    bidPrice = std::stoi(val);
  }
  if (askPrice != -1 || bidPrice != 1) {
    constructAndPassMarketData(bidPrice, askPrice, -1, -1);
  }
  // current volume is not obvious here, only gives 24hr volume
}
