#include "BitMEXListener.h"

#include <json/single_include/nlohmann/json.hpp>

BitMEXListener::BitMEXListener(DataManager &dataManager)
    : Listener("wss://www.bitmex.com/realtime",
               "{\"op\":\"subscribe\",\"args\":[\"instrument:XBTUSD\"]}",
               "BITMEX", dataManager) {}

void BitMEXListener::passJSON(nlohmann::json json) {
  if (json.contains("data")) {
    // Since this is tightly coupled to MarketData the implementation will
    // depend on how we tie that up with multiple exchanges
    /*
    if (!data) {
        data = new MarketData("Bitcoin", json.at("data")[0].at("askPrice"),
    json.at("data")[0].at("bidPrice"), json.at("data")[0].at("volume"));
        data->newMarketData();
    } else {
        if (json.at("data")[0].contains("askPrice")) {
            data->updateSell(json.at("data")[0].at("askPrice"));
            data->newMarketData();
        }
        if (json.at("data")[0].contains("bidPrice")) {
            data->updateBuy(json.at("data")[0].at("bidPrice"));
            data->newMarketData();
        }
        if (json.at("data")[0].contains("volume")) {
            data->updateVolume(json.at("data")[0].at("volume"));
            data->newMarketData();
        }
    }
     */
  }
}
