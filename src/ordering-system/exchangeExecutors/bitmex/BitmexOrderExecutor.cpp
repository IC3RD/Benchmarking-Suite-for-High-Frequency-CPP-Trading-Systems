#include "BitmexOrderExecutor.h"

#include <Poco/HMACEngine.h>
#include <ordering-system/exchangeExecutors/utils/SHA256Engine.h>

#include <chrono>
#include <iostream>

BitmexOrderExecutor::BitmexOrderExecutor() = default;

std::string BitmexOrderExecutor::parseOrder(const Order &order) {
  std::string currency = "XBTUSD";
  int quantity = order.getVolume();
  std::string output =
      "symbol=" + currency + "&side=" + (order.isBuyOrder() ? "Buy" : "Sell") +
      "&orderQty=" + std::to_string(quantity) +
      "&price=" + std::to_string(order.getPrice()) + "&ordType=Limit";
  return output;
}

void BitmexOrderExecutor::submitOrder(Order order) {
  std::string order_data = parseOrder(order);

  if (output) {
    PRINT("Submitting order with data: " + order_data + " to " +
          getExchangeName() + "...");
  }

  curlManager->addPostFields(order_data);
  std::string URL = getDestination();
  curlManager->addDestination(URL);
  BitmexOrderExecutor::generateHeaders(order_data);
  curlManager->appendHeadersToRequest();

  sendOrder();
}

std::string BitmexOrderExecutor::getDestination() {
  return "https://testnet.bitmex.com/api/v1/order";
  //    return "https://httpbin.org/post";
}

std::string BitmexOrderExecutor::getExchangeName() { return "BitMEX"; }

std::string BitmexOrderExecutor::getSecretKey() {
  return "_hTVt28pJk094DJI4HBU98V-GsBMiToqqvrOvjUcGhilKuMF";
}

std::string BitmexOrderExecutor::getPublicKey() {
  return "DQakAekZhCUpMyp8-oBjSZj0";
}

std::string BitmexOrderExecutor::generateTimestamp() {
  long api_duration = 14400;

  const auto time = std::chrono::system_clock::now();
  const auto current_time =
      std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch())
          .count();
  const auto expiry_time = current_time + api_duration;

  return std::to_string(expiry_time);
}

void BitmexOrderExecutor::generateHeaders(const std::string &data) {
  std::string timestamp = generateTimestamp();
  std::string signature =
      BitmexOrderExecutor::generateSignature(data, timestamp);
  curlManager->appendHeader("api-expires: " + timestamp);
  curlManager->appendHeader("api-key: " + getPublicKey());
  curlManager->appendHeader("api-signature: " + signature);
  curlManager->appendHeader("Content-Type: application/x-www-form-urlencoded");
  curlManager->appendHeader("Accept: application/json");
  curlManager->appendHeader("X-Requested-With: XMLHttpRequest");
}

std::string BitmexOrderExecutor::generateSignature(
    const std::string &message, const std::string &timestamp) {
  SHA256Engine engine{};
  std::string verb = "POST";
  std::string path = "/api/v1/order";
  Poco::HMACEngine<SHA256Engine> hmac{getSecretKey()};
  hmac.update(verb + path + timestamp + message);
  std::string hmac_hex = Poco::DigestEngine::digestToHex(hmac.digest());
  return hmac_hex;
}
