#include "BitMEXListener.h"

#include <json/single_include/nlohmann/json.hpp>

BitMEXListener::BitMEXListener(OrderBook &orderBook)
    : Listener("wss://www.bitmex.com/realtime",
               "{\"op\":\"subscribe\",\"args\":[\"orderBookL2:XBTUSD\"]}",
               Exchange::BITMEX, orderBook) {}

void BitMEXListener::passJSON(nlohmann::json json) {
  if (json.contains("data")) {
    int askPrice = -1;
    int bidPrice = -1;
    int askVolume = -1;
    int bidVolume = -1;

    if (json.at("data")[0].contains("askPrice")) {
      askPrice = json.at("data")[0].at("askPrice");
    }
    if (json.at("data")[0].contains("bidPrice")) {
      bidPrice = json.at("data")[0].at("bidPrice");
    }
    if (json.at("data")[0].contains("volume")) {
      askVolume = json.at("data")[0].at("volume");
      bidVolume = askVolume;
    }
    if (askPrice != -1 || bidPrice != -1 || askVolume != -1) {
      //constructAndPassMarketData(bidPrice, askPrice, bidVolume, askVolume);
    }
  }
}