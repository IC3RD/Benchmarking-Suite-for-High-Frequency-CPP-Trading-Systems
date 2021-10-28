#include "BitMEXApi.h"

#include <Poco/HMACEngine.h>
#include <curl/curl.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <deque>
#include <iostream>

#include "SHA256Engine.h"

using namespace std;

BitMEXApi::BitMEXApi(string apiKey, string apiSecret)
    : apiKey(apiKey), apiSecret(apiSecret){};

// Adds headers to curl request. See: https://www.bitmex.com/app/apiKeysUsage
void BitMEXApi::generateHeaders(CURL *curl, struct curl_slist **chunk,
                                Order order, string data) {
  *chunk = curl_slist_append(*chunk, "Accept:");

  /* Generating the api-expires header.*/
  long api_duration = 14400;

  // Get the UNIX timestamp of the expiry time.
  const auto time = std::chrono::system_clock::now();
  const auto current_time =
      std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch())
          .count();
  const auto expiry_time = current_time + api_duration;

  string api_expires_header = "api-expires:" + std::to_string(expiry_time);

  *chunk = curl_slist_append(*chunk, api_expires_header.c_str());

  /* Generating the api-key header.*/
  string api_key_header = "api-key:" + this->apiKey;

  *chunk = curl_slist_append(*chunk, api_key_header.c_str());

  /* Generating the api-signature header.*/
  SHA256Engine engine{};
  string verb = "POST";
  string path = "/api/v1/order";
  auto expires = expiry_time;
  //    string data = BitMEXApi::generatePostFields(order);

  cout << "> String to encode: "
       << verb + path + to_string(expires) + data.c_str() << "\n";

  Poco::HMACEngine<SHA256Engine> hmac{this->apiSecret};
  hmac.update(verb + path + to_string(expires) + data.c_str());

  string hmac_hex = Poco::DigestEngine::digestToHex(hmac.digest());
  string api_signature_header = "api-signature:" + hmac_hex;

  cout << "> HMAC-SHA256 output: " << hmac_hex << "\n";

  *chunk = curl_slist_append(*chunk, api_signature_header.c_str());

  /* Adding misc headers. */
  *chunk = curl_slist_append(*chunk,
                             "Content-Type: application/x-www-form-urlencoded");
  *chunk = curl_slist_append(*chunk, "Accept: application/json");
  *chunk = curl_slist_append(*chunk, "X-Requested-With: XMLHttpRequest");
}

string BitMEXApi::generatePostFields(Order order) {
  // Format an order object into a path string.
  // e.g: OrderObj => "symbol=XBTUSD&side=Buy&orderQty=1&price=55&ordType=Limit"

  // Can modify this later.
  string currency = "XBTUSD";
  // apparently this needs to be in multiples of 100 or you get Invalid
  // leavesQty for lotSize
  int quantity = 100;
  string output = "";

  output += "symbol=" + currency +
            "&side=" + (order.isBuyOrder() ? "Buy" : "Sell") +
            "&orderQty=" + to_string(quantity) +
            "&price=" + to_string(order.getPrice()) + "&ordType=Limit";

  return output;
}

void BitMEXApi::placeOrder(Order order) {
  // curl -X POST --header 'Content-Type: application/x-www-form-urlencoded'
  // --header 'Accept: application/json' --header 'X-Requested-With:
  // XMLHttpRequest' -d
  // 'symbol=XBTUSD&side=Buy&orderQty=1&price=55&ordType=Limit'
  // 'https://www.bitmex.com/api/v1/order'

  cout << "> Submitting Order: " << BitMEXApi::generatePostFields(order)
       << "\n";
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if (curl) {
    // Debugging purposes: set verbose mode to true.
    //        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://testnet.bitmex.com/api/v1/order");
    //        curl_easy_setopt(curl, CURLOPT_URL, "https://httpbin.org/post");
    string str_data = BitMEXApi::generatePostFields(order);
    //        char *output = curl_easy_escape(curl, str_data.c_str(),
    //        str_data.length());
    cout << "Data to be sent: " << str_data << '\n';
    //        str_data = output;
    cout << "Easy Escaped: " << str_data << '\n';
    //        curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, data);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str_data.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, str_data.length());

    // Add the headers.
    struct curl_slist *chunk = NULL;
    BitMEXApi::generateHeaders(curl, &chunk, order, str_data);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
    cout << "\n";
  }
}

string BitMEXApi::params(Order order) {
  string params = "{";
  return params + "\"symbol\": \"" + order.getSymbol() + "\", " +
         "\"price\": " + to_string(order.getPrice()) + ", " +
         "\"volume\": " + to_string(order.getVolume()) + "}";
}