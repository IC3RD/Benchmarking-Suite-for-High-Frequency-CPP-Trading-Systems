#include "BinanceOrderExecutor.h"

#include <curl/curl.h>

#include <chrono>

#include "Poco/DigestEngine.h"
#include "Poco/HMACEngine.h"
#include "Poco/JSON/Object.h"
#include "ordering-system/exchangeExecutors/utils/SHA256Engine.h"

void BinanceOrderExecutor::submitOrder(Order order) {
  std::string order_data = parseOrder(order);

  if (output) {
    PRINT("Posting order: " + order_data);
  }

  CURL *curl;
  curl = curl_easy_init();

  if (curl) {
    /* Set up request. */
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    std::string URL = getDestination();
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

BinanceOrderExecutor::BinanceOrderExecutor() : ExchangeOrderExecutor() {}

std::string BinanceOrderExecutor::getDestination() {
  // Amend if you are debugging.
  bool debug = false;
  if (debug) {
    return "https://httpbin.org/post";
  } else {
    return "https://testnet.binance.vision/api/v3/order?";
  }
}
std::string BinanceOrderExecutor::getSecretKey() {
  return "d1CE8YF6bPuOkjUPobN0DMf0NnEX5FrzW4chWQduxMFr412dEsV9c1kCcvRkKNPU";
}
std::string BinanceOrderExecutor::getPublicKey() {
  return "sBe2iw3BTx9bpOofw9ejD5pmAGc7qlVKp3qruGcGbCPtGenVtSEThdeh7WmpPoQq";
}
std::string BinanceOrderExecutor::getExchangeName() { return "Binance"; }
