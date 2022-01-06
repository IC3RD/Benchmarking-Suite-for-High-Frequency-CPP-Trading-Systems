#include "BitMEXListener.h"

#include <json/single_include/nlohmann/json.hpp>

BitMEXListener::BitMEXListener(OrderBook &orderBook)
    : Listener("wss://www.bitmex.com/realtime",
               "{\"op\":\"subscribe\",\"args\":[\"orderBookL2:XBTUSD\"]}",
               Exchange::BITMEX, orderBook) {}

void BitMEXListener::passJSON(nlohmann::json json) {
  if (json.contains("data") && json.at("action") == "insert") {
    if (json.at("data")[0].at("side") == "Sell") {
      long long price = json.at("data")[0].at("price");
      int volume = json.at("data")[0].at("size");
      collectOrderData(OrderTypes::BID, price, volume);
    }

    if (json.at("data")[0].at("side") == "Buy") {
      long long price = json.at("data")[0].at("price");
      int volume = json.at("data")[0].at("size");
      collectOrderData(OrderTypes::ASK, price, volume);
    }
  }
}