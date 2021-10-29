#include "CoinbaseOrderManager.h"
#include <Base64.h>
#include <Poco/DigestEngine.h>
#include <Poco/HMACEngine.h>
#include <Poco/JSON/Object.h>
#include <SHA256Engine.h>
#include <chrono>
#include <curl/curl.h>

// Macro to print things for debugging purposes.
#define DEBUG(x)                                                               \
  do {                                                                         \
    std::cout << "> " << x << std::endl;                                       \
  } while (0)

void CoinbaseOrderManager::submitOrder(Order order) {
  string order_data = parseOrder(order);
  DEBUG("Submitting order with data: " + order_data + " to " +
        getExchangeName() + "...");

  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();

  if (curl) {
    // Set up request.
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    string URL = getURL();
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, order_data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, order_data.length());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

    // Add required headers.
    struct curl_slist *chunk = nullptr;
    generateHeaders(&chunk, order_data);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }

    // Cleanup.
    curl_easy_cleanup(curl);
    cout << std::endl;
  }
}

string CoinbaseOrderManager::generateTimestamp() {
  const auto time = std::chrono::system_clock::now();
  const auto current_time =
      std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch())
          .count();
  return to_string(current_time);
}

void CoinbaseOrderManager::generateHeaders(struct curl_slist **chunk,
                                           const string &data) {
  *chunk = curl_slist_append(*chunk, "Accept: application/json");
  *chunk = curl_slist_append(*chunk, "Content-Type: application/json");
  *chunk = curl_slist_append(*chunk, "User-Agent: CoinbaseProAPI");
  *chunk =
      curl_slist_append(*chunk, ("cb-access-key:" + getPublicKey()).c_str());
  string timestamp = generateTimestamp();
  string signature = authenticate(data, timestamp);
  *chunk = curl_slist_append(*chunk, ("cb-access-sign:" + signature).c_str());
  *chunk =
      curl_slist_append(*chunk, ("cb-access-timestamp:" + timestamp).c_str());
  *chunk = curl_slist_append(*chunk, "cb-access-passphrase:c116en8tfv6");
}

string CoinbaseOrderManager::authenticate(const string &message,
                                          const string &timestamp) {
  string decoded;
  macaron::Base64::Decode(getSecretKey(), decoded);
  Poco::HMACEngine<SHA256Engine> hmac{decoded};
  // timestamp + method + requestPath + body
  string toSign = timestamp + "POST" + "/orders" + message.c_str();
  hmac.update(toSign);
  string digest = Poco::DigestEngine::digestToHex(hmac.digest());
  string hex_str = hex_to_string(digest);
  string encoded = macaron::Base64::Encode(hex_str);
  return encoded;
}

string CoinbaseOrderManager::parseOrder(const Order &order) {
  Poco::JSON::Object::Ptr json = new Poco::JSON::Object;

  json->set("side", order.isBuyOrder() ? "buy" : "sell");

  // Assuming is BTC for now...
  json->set("product_id", "BTC-USD");

  // Price must be in units of 'quote_increment' product units.
  // For BTC-USD it's 0.01. Therefore, $100 = 10000 units.
  // If we'd like to use multiple coins (likely), we should ask via websocket
  // for 'quote_increment' for each type of coin.
  // TODO: What should be price unit in the 'Order' class?
  // FIXME: Change price value depending on units in 'Order' class.
  json->set("price", to_string(order.getPrice()));

  json->set("size", to_string(order.getVolume()));

  std::stringstream ss;
  Poco::JSON::Stringifier::stringify(json, ss);
  return ss.str();
}

CoinbaseOrderManager::CoinbaseOrderManager() : OrderManager() {}

string CoinbaseOrderManager::getURL() {
  // Amend if you are debugging.
  bool debug = false;
  if (debug) {
    return "https://httpbin.org/post";
  } else {
    return "https://api-public.sandbox.pro.coinbase.com/orders";
  }
}

string CoinbaseOrderManager::getSecretKey() {
  return "jgEtlhOBhGESP7JUQ2w6Dm46Wbar8zWv5ib3PEYfTC7avQ8M8ohxNHvLESnJGHhRYlOZp"
         "iMzPiEaU8onVlNgSg==";
}
string CoinbaseOrderManager::getPublicKey() {
  return "00dcf06c3d7402c3272eef11593446b0";
}

string CoinbaseOrderManager::getExchangeName() { return "Coinbase"; }

std::string CoinbaseOrderManager::hex_to_string(const std::string &in) {
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
