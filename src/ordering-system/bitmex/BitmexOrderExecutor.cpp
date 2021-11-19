#include "BitmexOrderExecutor.h"

#include <Poco/HMACEngine.h>
#include <curl/curl.h>
#include <utils/SHA256Engine.h>

#include <chrono>
#include <iostream>
#include <utility>

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

  printOrderDetails(order_data);

  CURL *curl;
  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    std::string URL = getURL();
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, order_data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, order_data.length());

    /* Add the required headers. */
    struct curl_slist *chunk = nullptr;
    BitmexOrderExecutor::generateHeaders(&chunk, order_data);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    sendOrder(curl);
  }
}

std::string BitmexOrderExecutor::getURL() {
  return "https://testnet.bitmex.com/api/v1/order";
}

std::string BitmexOrderExecutor::getExchangeName() { return "BitMEX"; }

std::string BitmexOrderExecutor::getSecretKey() {
  return this->secret_key;
}

std::string BitmexOrderExecutor::getPublicKey() {
  return this->public_key;
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

void BitmexOrderExecutor::generateHeaders(struct curl_slist **chunk,
                                          const std::string &data) {
  std::string timestamp = generateTimestamp();
  *chunk = curl_slist_append(*chunk, ("api-expires: " + timestamp).c_str());
  *chunk = curl_slist_append(*chunk, ("api-key: " + getPublicKey()).c_str());
  std::string signature =
      BitmexOrderExecutor::generateSignature(data, timestamp);
  *chunk = curl_slist_append(*chunk, ("api-signature: " + signature).c_str());

  *chunk = curl_slist_append(*chunk,
                             "Content-Type: application/x-www-form-urlencoded");
  *chunk = curl_slist_append(*chunk, "Accept: application/json");
  *chunk = curl_slist_append(*chunk, "X-Requested-With: XMLHttpRequest");
}

std::string BitmexOrderExecutor::generateSignature(
    const std::string &message, const std::string &timestamp) {
  SHA256Engine engine{};
  std::string verb = "POST";
  std::string path = "/api/v1/order";
  Poco::HMACEngine<SHA256Engine> hmac{getSecretKey()};
  hmac.update(verb + path + timestamp + message.c_str());
  std::string hmac_hex = Poco::DigestEngine::digestToHex(hmac.digest());

  return hmac_hex;
}
BitmexOrderExecutor::BitmexOrderExecutor(std::string secret_key,
                                         std::string public_key)
    : OrderExecutor(std::move(secret_key), std::move(public_key)) {}
