#include "BinanceOrderExecutor.h"

#include <chrono>

#include "Poco/DigestEngine.h"
#include "Poco/HMACEngine.h"
#include "Poco/JSON/Object.h"
#include "ordering-system/exchangeExecutors/utils/SHA256Engine.h"

void BinanceOrderExecutor::submitOrder(Order order) {
  mtx.lock();
  curlManager->initCurl();
  std::string order_data = parseOrder(order);

  if (output) {
    PRINT("Submitting order with data: " + order_data + " to " +
          getExchangeName() + "...");
  }

  std::string URL = getDestination();
  curlManager->addDestination(URL);
  order_data += "&signature=" + authenticate(order_data);
  curlManager->addPostFields(order_data);
  generateHeaders();
  curlManager->appendHeadersToRequest();
  sendOrder();
  mtx.unlock();
}

std::string BinanceOrderExecutor::generateTimestamp() {
  const auto time = std::chrono::system_clock::now();
  const auto current_time =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          time.time_since_epoch())
          .count();
  return std::to_string(current_time);
}

void BinanceOrderExecutor::generateHeaders() {
  curlManager->addPostFields("X-MBX-APIKEY: " + getPublicKey());
  curlManager->addPostFields("Content-Type: application/x-www-form-urlencoded");
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
  int quantity = order.getVolume();
  std::string output;
  output +=
      "symbol=" + currency + "&side=" + (order.isBuyOrder() ? "BUY" : "SELL") +
      "&type=LIMIT&timeInForce=GTC" + "&quantity=" + std::to_string(quantity) +
      "&price=" + std::to_string(order.getPrice() / 100) + "&recvWindow=60000" +
      "&timestamp=" + timestamp;
  return output;
}

BinanceOrderExecutor::BinanceOrderExecutor() : ExchangeOrderExecutor() {}

std::string BinanceOrderExecutor::getDestination() {
  return "https://testnet.binance.vision/api/v3/order?";
}

std::string BinanceOrderExecutor::getSecretKey() {
  return "d1CE8YF6bPuOkjUPobN0DMf0NnEX5FrzW4chWQduxMFr412dEsV9c1kCcvRkKNPU";
}
std::string BinanceOrderExecutor::getPublicKey() {
  return "sBe2iw3BTx9bpOofw9ejD5pmAGc7qlVKp3qruGcGbCPtGenVtSEThdeh7WmpPoQq";
}
std::string BinanceOrderExecutor::getExchangeName() { return "Binance"; }
