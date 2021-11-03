#pragma once

#include <curl/curl.h>

#include <string>

#include "Order.h"

class BitMEXApi {
 public:
  BitMEXApi(std::string apiKey, std::string apiSecret);
  std::string params(Order order);
  void placeOrder(Order order);
  void generateHeaders(CURL *curl, struct curl_slist **chunk, Order order,
                       std::string data);
  std::string generatePostFields(Order order);

 private:
  std::string domain = "https://testnet.bitmex.com";
  std::string apiKey;
  std::string apiSecret;
  std::string baseURI = "https://testnet.bitmex.com/api/v1";
};