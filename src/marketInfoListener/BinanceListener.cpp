#include "BinanceListener.h"

#include <iomanip>
#include <iostream>
#include <json/single_include/nlohmann/json.hpp>
#include <string>

BinanceListener::BinanceListener(DataManager &dataManager, OrderBook &orderBook)
    : Listener(
          "wss://stream.binance.com:9443/ws",
          "{\"method\":\"SUBSCRIBE\",\"params\":[\"btcusdt@depth\"],\"id\":1}",
          Exchange::BINANCE, dataManager, orderBook) {}

// reference:
// https://github.com/binance/binance-spot-api-docs/blob/master/web-socket-streams.md
void BinanceListener::passJSON(nlohmann::json json) {
  int askPrice, askVolume, bidPrice, bidVolume = -1;
  if (json.contains("a")) {
    askPrice = json.at("a")[0][0];
    askVolume = json.at("a")[0][1];
  }
  if (json.contains("b")) {
    bidPrice = json.at("b")[0][0];
    bidVolume = json.at("b")[0][1];
  }
  if (askPrice != -1 || bidPrice != -1) {
    constructAndPassMarketData(bidPrice, askPrice, bidVolume, askVolume);
  }
}
