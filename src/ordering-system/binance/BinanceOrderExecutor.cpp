#include "BinanceOrderExecutor.h"

#include <curl/curl.h>

#include <chrono>
#include <utility>

#include "Poco/DigestEngine.h"
#include "Poco/HMACEngine.h"
#include "Poco/JSON/Object.h"
#include "utils/SHA256Engine.h"

void BinanceOrderExecutor::submitOrder(Order order) {
  std::string order_data = parseOrder(order);

  printOrderDetails(order_data);

  CURL *curl;
  curl = curl_easy_init();

  if (curl) {
    /* Set up request. */
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    std::string URL = getURL();
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

    /* Add the sha256 signature to the post fields. */
    order_data += "&signature=" + authenticate(order_data);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, order_data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, order_data.length());

    /* Add required headers. */
    struct curl_slist *chunk = nullptr;
    generateHeaders(&chunk);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    sendOrder(curl);
  }
}

std::string BinanceOrderExecutor::generateTimestamp() {
  const auto time = std::chrono::system_clock::now();
  const auto current_time =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          time.time_since_epoch())
          .count();
  return std::to_string(current_time);
}

void BinanceOrderExecutor::generateHeaders(struct curl_slist **chunk) {
  *chunk =
      curl_slist_append(*chunk, ("X-MBX-APIKEY: " + getPublicKey()).c_str());
  *chunk = curl_slist_append(*chunk,
                             "Content-Type: "
                             "application/x-www-form-urlencoded");
}

std::string BinanceOrderExecutor::authenticate(std::string message) {
  Poco::HMACEngine<SHA256Engine> hmac{getSecretKey()};
  hmac.update(message);
  std::string digest = Poco::DigestEngine::digestToHex(hmac.digest());
  return digest;
}

std::string BinanceOrderExecutor::parseOrder(const Order &order) {
  Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
  std::string currency = "BTCUSDT";
  std::string timestamp = generateTimestamp();
  double quantity = 0.005;
  std::string output;
  output +=
      "symbol=" + currency + "&side=" + (order.isBuyOrder() ? "BUY" : "SELL") +
      "&type=LIMIT&timeInForce=GTC" + "&quantity=" + std::to_string(quantity) +
      "&price=" + std::to_string(order.getPrice()) + "&recvWindow=60000" +
      "&timestamp=" + timestamp;
  return output;
}

std::string BinanceOrderExecutor::getURL() {
  bool debug = false;
  if (debug) {
    return "https://httpbin.org/post";
  } else {
    return "https://testnet.binance.vision/api/v3/order?";
  }
}
std::string BinanceOrderExecutor::getSecretKey() {
  return this->secret_key;
}
std::string BinanceOrderExecutor::getPublicKey() {
  return this->public_key;
}
std::string BinanceOrderExecutor::getExchangeName() { return "Binance"; }

BinanceOrderExecutor::BinanceOrderExecutor(std::string secret_key,
                                           std::string public_key)
    : OrderExecutor(std::move(secret_key), std::move(public_key)) {}
