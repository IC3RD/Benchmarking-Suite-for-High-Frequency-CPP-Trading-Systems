#include "FTXListener.h"

#include <iomanip>
#include <iostream>
#include <json/single_include/nlohmann/json.hpp>
#include <string>

FTXListener::FTXListener(DataManager &dataManager, OrderBook &orderBook)
    : Listener("wss://ftx.com/ws/",
               "{\"op\": \"subscribe\", \"channel\": \"orderbook\", "
               "\"market\": \"BTC-PERP\"}",
               Exchange::FTX, dataManager, orderBook) {}

// reference: https://docs.ftx.com/#websocket-api
void FTXListener::passJSON(nlohmann::json json) {
  if (json.contains("channel") && json.contains("data")) {
    // auto *asks = json.at("data").at("asks");
    int askPrice = -1;
    int bidPrice = -1;
    int askVolume = -1;
    int bidVolume = -1;
    if (json.at("data").at("asks").size() > 0) {
      int askPrice = json.at("data").at("asks")[0][0];
      int askVolume = json.at("data").at("asks")[0][1];
    }
    if (json.at("data").at("bids").size() > 0) {
      int bidPrice = json.at("data").at("bids")[0][0];
      int bidVolume = json.at("data").at("bids")[0][1];
    }
    if (askPrice != -1 || bidPrice != -1) {
      constructAndPassMarketData(bidPrice, bidVolume, askPrice, askVolume);
    }
  }
}
