#include "BitmexOrderManager.h"
#include <Poco/HMACEngine.h>
#include <SHA256Engine.h>
#include <chrono>
#include <cstdio>
#include <curl/curl.h>
#include <iostream>

// Macro to print things for debugging purposes.
#define DEBUG(x)                                                               \
  do {                                                                         \
    std::cout << "> " << x << std::endl;                                       \
  } while (0)

BitmexOrderManager::BitmexOrderManager() = default;

string BitmexOrderManager::parseOrder(const Order &order) {
  // TODO: Add support for other coins.
  string currency = "XBTUSD";

  // This needs to be in multiples of 100.
  int quantity = 100;
  string output = "symbol=" + currency +
                  "&side=" + (order.isBuyOrder() ? "Buy" : "Sell") +
                  "&orderQty=" + to_string(quantity) +
                  "&price=" + to_string(order.getPrice()) + "&ordType=Limit";

  return output;
}

void BitmexOrderManager::submitOrder(Order order) {
  string order_data = parseOrder(order);

  DEBUG("Submitting order with data: " + order_data + " to " +
        getExchangeName() + "...");

  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    string URL = getURL();
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, order_data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, order_data.length());

    // Add the headers.
    struct curl_slist *chunk = nullptr;
    BitmexOrderManager::generateHeaders(&chunk, order_data);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    // Cleanup.
    curl_easy_cleanup(curl);
    std::cout << std::endl;
  }
}

string BitmexOrderManager::getURL() {
  return "https://testnet.bitmex.com/api/v1/order";
}

string BitmexOrderManager::getExchangeName() { return "BitMEX"; }

string BitmexOrderManager::getSecretKey() {
  return "_hTVt28pJk094DJI4HBU98V-GsBMiToqqvrOvjUcGhilKuMF";
}

string BitmexOrderManager::getPublicKey() { return "DQakAekZhCUpMyp8-oBjSZj0"; }

string BitmexOrderManager::generateTimestamp() {
  long api_duration = 14400;

  const auto time = std::chrono::system_clock::now();
  const auto current_time =
      std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch())
          .count();
  const auto expiry_time = current_time + api_duration;

  return to_string(expiry_time);
}

void BitmexOrderManager::generateHeaders(struct curl_slist **chunk,
                                         const string &data) {

  string timestamp = generateTimestamp();
  *chunk = curl_slist_append(*chunk, ("api-expires: " + timestamp).c_str());
  *chunk = curl_slist_append(*chunk, ("api-key: " + getPublicKey()).c_str());
  string signature = BitmexOrderManager::generateSignature(data, timestamp);
  *chunk = curl_slist_append(*chunk, ("api-signature: " + signature).c_str());

  *chunk = curl_slist_append(*chunk,
                             "Content-Type: application/x-www-form-urlencoded");
  *chunk = curl_slist_append(*chunk, "Accept: application/json");
  *chunk = curl_slist_append(*chunk, "X-Requested-With: XMLHttpRequest");
}

string BitmexOrderManager::generateSignature(const string &message,
                                             const string &timestamp) {

  SHA256Engine engine{};
  string verb = "POST";
  string path = "/api/v1/order";
  Poco::HMACEngine<SHA256Engine> hmac{getSecretKey()};
  hmac.update(verb + path + timestamp + message.c_str());
  string hmac_hex = Poco::DigestEngine::digestToHex(hmac.digest());

  return hmac_hex;
}
