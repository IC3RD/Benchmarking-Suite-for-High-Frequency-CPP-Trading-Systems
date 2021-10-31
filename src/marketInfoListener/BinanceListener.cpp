#include "BinanceListener.h"

#include <iomanip>
#include <iostream>
#include <json/single_include/nlohmann/json.hpp>
#include <string>

BinanceListener::BinanceListener(DataManager &dataManager)
    : Listener(
          "wss://stream.binance.com:9443/ws",
          "{\"method\":\"SUBSCRIBE\",\"params\":[\"btcusdt@depth\"],\"id\":1}",
          "BINANCE", dataManager) {}

// reference:
// https://github.com/binance/binance-spot-api-docs/blob/master/web-socket-streams.md
void BinanceListener::passJSON(nlohmann::json json) {
  if (json.contains("a")) {
    std::string askPrice = json.at("a")[0][0];
  }
  if (json.contains("b")) {
    std::string bidPrice = json.at("b")[0][0];
  }
}
