//
// Created by panos on 10/29/21.
//
#include "BinanceOrderManager.h"
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

void BinanceOrderManager::submitOrder(Order order) {
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

        //Add the sha256 signature to the post fields
        order_data += "&signature=" + authenticate(order_data);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, order_data.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, order_data.length());

        // Add required headers.
        struct curl_slist *chunk = NULL;
        generateHeaders(&chunk);
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

string BinanceOrderManager::generateTimestamp() {
    const auto time = std::chrono::system_clock::now();
    const auto current_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch())
                    .count();
    return to_string(current_time);
}

void BinanceOrderManager::generateHeaders(struct curl_slist **chunk) {

    *chunk = curl_slist_append(*chunk, ("X-MBX-APIKEY: " + getPublicKey()).c_str());
    *chunk = curl_slist_append(*chunk, "Content-Type: application/x-www-form-urlencoded");
}

string BinanceOrderManager::authenticate(string message) {

    Poco::HMACEngine<SHA256Engine> hmac{getSecretKey()};

    hmac.update(message);

    string digest = Poco::DigestEngine::digestToHex(hmac.digest());
    //string encoded = base64_encode(digest);
    return digest;
}

//curl -H "X-MBX-APIKEY: vmPUZE6mv9SD5VNHk4HlWFsOr6aKE2zvsw0MuIgwCIPy6utIco14y7Ju91duEh8A" -X
// POST 'https://api.binance.com/api/v3/order' -d
// 'symbol=LTCBTC&side=BUY&type=LIMIT&timeInForce=GTC&quantity=1&price=0.1&recvWindow=5000&timestamp=1499827319559&signature=c8db56825ae71d6d79447849e617115f4a920fa2acdcab2b053c4b2838bd6b71'
string BinanceOrderManager::parseOrder(const Order& order) {
    Poco::JSON::Object::Ptr json = new Poco::JSON::Object;

    // Price must be in units of 'quote_increment' product units.
    // For BTC-USD it's 0.01. Therefore, $100 = 10000 units.
    // If we'd like to use multiple coins (likely), we should ask via websocket
    // for 'quote_increment' for each type of coin.
    // TODO: What should be price unit in the 'Order' class?
    // FIXME: Change price value depending on units in 'Order' class.

    string currency = "BTCUSDT";

    string timestamp = generateTimestamp();

    int quantity = 100;
    string output;

    output += "symbol=" + currency + "&side=" + (order.isBuyOrder() ? "BUY" : "SELL") + "&type=LIMIT&timeInForce=GTC" + "&quantity=" +
              to_string(quantity) + "&price=" + to_string(order.getPrice()) + "&recvWindow=60000" + "&timestamp=" + timestamp;

    return output;
}

BinanceOrderManager::BinanceOrderManager() : OrderManager() {}

string BinanceOrderManager::getURL() {
    // Amend if you are debugging.
    bool debug = false;
    if (debug) {
        return "https://httpbin.org/post";
    } else {
        return "https://testnet.binance.vision/api/v3/order?";
    }
}
string BinanceOrderManager::getSecretKey() {
    return "a5d4715abe345ff2df4833d1276f56b6bcd08bdb4578d7148974aef28104ad17"; //this is wrong key
}
string BinanceOrderManager::getPublicKey() {
    return "aa5c6c0c9793ef57e72d3794d8beb1a965a15a6279faaf179827005af1e09fa6"; //this too
}

std::string BinanceOrderManager::base64_encode(const std::string &in) {

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

std::string BinanceOrderManager::base64_decode(const std::string &in) {

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

