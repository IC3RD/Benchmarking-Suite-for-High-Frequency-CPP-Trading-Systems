#include "CoinbaseOrderExecutor.h"

#include <Poco/DigestEngine.h>
#include <Poco/HMACEngine.h>
#include <Poco/JSON/Object.h>
#include <ordering-system/exchangeExecutors/debug.h>
#include <ordering-system/exchangeExecutors/utils/Base64.h>
#include <ordering-system/exchangeExecutors/utils/SHA256Engine.h>

#include <chrono>

void CoinbaseOrderExecutor::submitOrder(Order order) {
  std::string order_data = parseOrder(order);

  if (output) {
    PRINT("Submitting order with data: " + order_data + " to " +
          getExchangeName() + "...");
  }

  CURL *curl;
  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    std::string URL = getDestination();
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, order_data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, order_data.length());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

    struct curl_slist *chunk = nullptr;
    generateHeaders(&chunk, order_data);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    sendOrder(curl);
  }
}

std::string CoinbaseOrderExecutor::generateTimestamp() {
  const auto time = std::chrono::system_clock::now();
  const auto current_time =
      std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch())
          .count();
  return std::to_string(current_time);
}

void CoinbaseOrderExecutor::generateHeaders(struct curl_slist **chunk,
                                            const std::string &data) {
  *chunk = curl_slist_append(*chunk, "Accept: application/json");
  *chunk = curl_slist_append(*chunk, "Content-Type: application/json");
  *chunk = curl_slist_append(*chunk, "User-Agent: CoinbaseProAPI");
  *chunk =
      curl_slist_append(*chunk, ("cb-access-key:" + getPublicKey()).c_str());
  std::string timestamp = generateTimestamp();
  std::string signature = authenticate(data, timestamp);
  *chunk = curl_slist_append(*chunk, ("cb-access-sign:" + signature).c_str());
  *chunk =
      curl_slist_append(*chunk, ("cb-access-timestamp:" + timestamp).c_str());
  *chunk = curl_slist_append(*chunk, "cb-access-passphrase:c116en8tfv6");
}

std::string CoinbaseOrderExecutor::authenticate(const std::string &message,
                                                const std::string &timestamp) {
  std::string decoded;
  macaron::Base64::Decode(getSecretKey(), decoded);
  Poco::HMACEngine<SHA256Engine> hmac{decoded};
  std::string toSign = timestamp + "POST" + "/orders" + message.c_str();
  hmac.update(toSign);
  std::string digest = Poco::DigestEngine::digestToHex(hmac.digest());
  std::string hex_str = hex_to_string(digest);
  std::string encoded = macaron::Base64::Encode(hex_str);
  return encoded;
}

std::string CoinbaseOrderExecutor::parseOrder(const Order &order) {
  Poco::JSON::Object::Ptr json = new Poco::JSON::Object;
  json->set("side", order.isBuyOrder() ? "buy" : "sell");
  json->set("product_id", "BTC-USD");
  json->set("price", std::to_string(order.getPrice() / 100));
  json->set("size", std::to_string(order.getVolume()));
  std::stringstream ss;
  Poco::JSON::Stringifier::stringify(json, ss);
  return ss.str();
}

CoinbaseOrderExecutor::CoinbaseOrderExecutor() : ExchangeOrderExecutor() {}

std::string CoinbaseOrderExecutor::getDestination() {
  // Amend if you are debugging.
  bool debug = false;
  if (debug) {
    return "https://httpbin.org/post";
  } else {
    return "https://api-public.sandbox.pro.coinbase.com/orders";
  }
}

std::string CoinbaseOrderExecutor::getSecretKey() {
  return "jgEtlhOBhGESP7JUQ2w6Dm46Wbar8zWv5ib3PEYfTC7avQ8M8ohxNHvLESnJGHhRYlOZp"
         "iMzPiEaU8onVlNgSg==";
}
std::string CoinbaseOrderExecutor::getPublicKey() {
  return "00dcf06c3d7402c3272eef11593446b0";
}

std::string CoinbaseOrderExecutor::getExchangeName() { return "Coinbase"; }

std::string CoinbaseOrderExecutor::hex_to_string(const std::string &in) {
  std::string output;

  if ((in.length() % 2) != 0) {
    throw std::runtime_error("String is not valid length ...");
  }

  size_t cnt = in.length() / 2;

  for (size_t i = 0; cnt > i; ++i) {
    uint32_t s = 0;
    std::stringstream ss;
    ss << std::hex << in.substr(i * 2, 2);
    ss >> s;

    output.push_back(static_cast<unsigned char>(s));
  }

  return output;
}
