#include "FTXListener.h"

#include <iomanip>
#include <iostream>
#include <json/single_include/nlohmann/json.hpp>
#include <string>

FTXListener::FTXListener()
    : Listener("wss://ftx.com/ws/",
               "{\"op\": \"subscribe\", \"channel\": \"orderbook\", "
               "\"market\": \"BTC-PERP\"}",
               "FTX") {}

// reference: https://docs.ftx.com/#websocket-api
void FTXListener::passJSON(nlohmann::json json) {
  if (json.contains("channel") && json.contains("data")) {
    // auto *asks = json.at("data").at("asks");
    if (json.at("data").at("asks").size() > 0) {
      int askPrice = json.at("data").at("asks")[0][0];
      // update marketdata
    }
    if (json.at("data").at("bids").size() > 0) {
      int bidPrice = json.at("data").at("bids")[0][0];
      // update marketdata
    }
  }
}
