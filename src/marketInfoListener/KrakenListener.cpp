#include "KrakenListener.h"

#include <iomanip>
#include <iostream>
#include <json/single_include/nlohmann/json.hpp>
#include <string>

#include "../exchange/Exchange.h"

KrakenListener::KrakenListener(OrderBook &orderBook)
    : Listener(
          "wss://ws.kraken.com/",
          "{\"event\":\"subscribe\", \"subscription\":{\"name\":\"book\"}, "
          "\"pair\":[\"BTC/USD\"]}",
          Exchange::KRAKEN, orderBook) {}

// reference: https://docs.kraken.com/websockets/#message-ticker
void KrakenListener::passJSON(nlohmann::json json) {
  // Have to do weird checking since the second json element is anonymous
  if (json.contains("connectionID")) {
    // std::cout << "contains connection";
  } else if (json.contains("event") && json.at("event") == "heartbeat") {
    // std::cout << "heartbeat";
  } else if (!json.contains("channelID")) {
    auto json1 = json[1];
    if (json1.contains("as")) {
      for (auto ask : json1.at("as")) {
        std::string askPrice = ask[0];
        std::string askVolume = ask[1];
        constructAndPassOrderData(
            OrderTypes::ASK, (int)std::stod(askPrice) * 100, stod(askVolume));
      }
    }
    if (json1.contains("bs")) {
      for (auto bid : json1.at("bs")) {
        std::string bidPrice = bid[0];
        std::string bidVolume = bid[1];
        constructAndPassOrderData(
            OrderTypes::BID, (int)std::stod(bidPrice) * 100, stod(bidVolume));
      }
    }
    if (json1.contains("a")) {
      for (auto ask : json1.at("a")) {
        std::string askPrice = ask[0];
        std::string askVolume = ask[1];
        constructAndPassOrderData(
            OrderTypes::ASK, (int)std::stod(askPrice) * 100, stod(askVolume));
      }
    }
    if (json1.contains("b")) {
      for (auto bid : json1.at("b")) {
        std::string bidPrice = bid[0];
        std::string bidVolume = bid[1];
        constructAndPassOrderData(
            OrderTypes::BID, (int)std::stod(bidPrice) * 100, stod(bidVolume));
      }
    }
  }
}
