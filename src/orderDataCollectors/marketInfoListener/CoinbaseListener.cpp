#include "CoinbaseListener.h"

#include <iomanip>
#include <iostream>
#include <json/single_include/nlohmann/json.hpp>
#include <string>

CoinbaseListener::CoinbaseListener(OrderBook &orderBook)
    : Listener("wss://ws-feed.exchange.coinbase.com",
               "{\"type\": \"subscribe\", \"product_ids\": [\"BTC-USD\"], "
               "\"channels\": [\"ticker\", \"level2\"]}",
               Exchange::COINBASE, orderBook) {}

// reference: https://docs.cloud.coinbase.com/exchange/docs/channels
void CoinbaseListener::passJSON(nlohmann::json json) {
  if (json.contains("type")) {
    if (json.at("type") == "snapshot") {
      if (json.contains("bids")) {
        for (auto bid : json.at("bids")) {
          std::string priceS = bid[0];
          std::string volumeS = bid[1];
          collectOrderData(OrderTypes::BID, std::stoll(priceS),
                           std::stod(volumeS));
        }
      }
      if (json.contains("asks")) {
        for (auto ask : json.at("asks")) {
          std::string priceS = ask[0];
          std::string volumeS = ask[1];
          collectOrderData(OrderTypes::ASK, std::stoll(priceS),
                           std::stod(volumeS));
        }
      }
    }
    if (json.at("type") == "l2update") {
      if (json.contains("changes")) {
        for (auto change : json.at("changes")) {
          OrderTypes::OrderType type;
          if (change[0] == "buy") {
            type = OrderTypes::BID;
          } else {
            type = OrderTypes::ASK;
          }
          std::string priceS = change[1];
          std::string volumeS = change[2];
          collectOrderData(type, std::stoll(priceS), std::stod(volumeS));
        }
      }
    }
  }
}
