#include "CoinbaseOrderManager.h"
#include <Poco/DigestEngine.h>
#include <Poco/HMACEngine.h>
#include <Poco/JSON/Object.h>
#include <SHA256Engine.h>
#include <chrono>
#include <curl/curl.h>

// Macro to print things for debugging purposes.
#define DEBUG(x)                                                               \
  do {                                                                         \
    std::cout << x << std::endl;                                               \
  } while (0)

void CoinbaseOrderManager::submitOrder(Order order) {
  string order_data = parseOrder(order);
  DEBUG("Posting order of " + order_data);

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

    // Add required headers.
    struct curl_slist *chunk = NULL;
    generateHeaders(&chunk, order_data);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
    cout << "\n";
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
                                           string data) {
  *chunk = curl_slist_append(*chunk, "Accept: application/json");
  *chunk = curl_slist_append(*chunk, "Content-Type: application/json");
  *chunk = curl_slist_append(*chunk, "User-Agent: CPPDesignPatternsAgent");
  *chunk =
      curl_slist_append(*chunk, ("cb-access-key: " + getPublicKey()).c_str());
  string timestamp = generateTimestamp();
  string signature = authenticate(data, timestamp);
  *chunk = curl_slist_append(*chunk, ("cb-access-sign: " + signature).c_str());
  *chunk =
      curl_slist_append(*chunk, ("cb-access-timestamp: " + timestamp).c_str());
  *chunk = curl_slist_append(*chunk, "cb-access-passphrase: c116en8tfv6");
}

string CoinbaseOrderManager::authenticate(string message, string timestamp) {

  Poco::HMACEngine<SHA256Engine> hmac{getSecretKey()};

  // timestamp + method + requestPath + body
  string toSign = timestamp + "POST" + "/orders" + message;
  string decoded = base64_decode(toSign);
  hmac.update(decoded);

  string digest = Poco::DigestEngine::digestToHex(hmac.digest());
  string encoded = base64_encode(digest);
  return encoded;
}

string CoinbaseOrderManager::parseOrder(Order order) {
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
  bool debug = true;
  if (debug) {
    return "https://httpbin.org/post";
  } else {
    return "https://api-public.sandbox.pro.coinbase.com";
  }
}
string CoinbaseOrderManager::getSecretKey() {
  return "ASK JAKE FOR SECRET KEY";
}
string CoinbaseOrderManager::getPublicKey() {
  return "00dcf06c3d7402c3272eef11593446b0";
}

std::string CoinbaseOrderManager::base64_encode(const std::string &in) {

  std::string out;

  int val = 0, valb = -6;
  for (unsigned char c : in) {
    val = (val << 8) + c;
    valb += 8;
    while (valb >= 0) {
      out.push_back(
          "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
              [(val >> valb) & 0x3F]);
      valb -= 6;
    }
  }
  if (valb > -6)
    out.push_back(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
            [((val << 8) >> (valb + 8)) & 0x3F]);
  while (out.size() % 4)
    out.push_back('=');
  return out;
}

std::string CoinbaseOrderManager::base64_decode(const std::string &in) {

  std::string out;

  std::vector<int> T(256, -1);
  for (int i = 0; i < 64; i++)
    T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] =
        i;

  int val = 0, valb = -8;
  for (unsigned char c : in) {
    if (T[c] == -1)
      break;
    val = (val << 6) + T[c];
    valb += 6;
    if (valb >= 0) {
      out.push_back(char((val >> valb) & 0xFF));
      valb -= 8;
    }
  }
  return out;
}
