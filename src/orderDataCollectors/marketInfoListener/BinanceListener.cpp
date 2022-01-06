#include "BinanceListener.h"

#include <iomanip>
#include <iostream>
#include <json/single_include/nlohmann/json.hpp>
#include <string>

BinanceListener::BinanceListener(OrderBook &orderBook)
    : Listener(
          "wss://stream.binance.com:9443/ws",
          "{\"method\":\"SUBSCRIBE\",\"params\":[\"btcusdt@depth\"],\"id\":1}",
          Exchange::BINANCE, orderBook) {
  lastUpdated = 0;
}

// reference:
// https://github.com/binance/binance-spot-api-docs/blob/master/web-socket-streams.md
void BinanceListener::passJSON(nlohmann::json json) {
  if (json.contains("e") && json.contains("u") && json.contains("U") &&
      json.contains("a") && json.contains("b")) {
    if (json.at("e") == "depthUpdate" && json.at("U") > lastUpdated) {
      for (auto ask : json.at("a")) {
        std::string askPrice = ask[0];
        std::string askVolume = ask[1];
        collectOrderData(OrderTypes::ASK, std::stoll(askPrice) * 100,
                         std::stod(askVolume));
      }

      for (auto bid : json.at("b")) {
        std::string bidPrice = bid[0];
        std::string bidVolume = bid[1];
        collectOrderData(OrderTypes::BID, std::stoll(bidPrice) * 100,
                         std::stod(bidVolume));
      }
      lastUpdated = json.at("u");
    }
  }
}
