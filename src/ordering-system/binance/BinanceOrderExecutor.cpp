//
// Created by panos on 10/29/21.
//
#include "BinanceOrderExecutor.h"
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

void BinanceOrderExecutor::submitOrder(Order order) {
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

string BinanceOrderExecutor::generateTimestamp() {
    const auto time = std::chrono::system_clock::now();
    const auto current_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch())
                    .count();
    return to_string(current_time);
}

void BinanceOrderExecutor::generateHeaders(struct curl_slist **chunk) {

    *chunk = curl_slist_append(*chunk, ("X-MBX-APIKEY: " + getPublicKey()).c_str());
    *chunk = curl_slist_append(*chunk, "Content-Type: application/x-www-form-urlencoded");
}

string BinanceOrderExecutor::authenticate(string message) {

    Poco::HMACEngine<SHA256Engine> hmac{getSecretKey()};

    hmac.update(message);

    string digest = Poco::DigestEngine::digestToHex(hmac.digest());
    //string encoded = base64_encode(digest);
    return digest;
}

//curl -H "X-MBX-APIKEY: vmPUZE6mv9SD5VNHk4HlWFsOr6aKE2zvsw0MuIgwCIPy6utIco14y7Ju91duEh8A" -X
// POST 'https://api.binance.com/api/v3/order' -d
// 'symbol=LTCBTC&side=BUY&type=LIMIT&timeInForce=GTC&quantity=1&price=0.1&recvWindow=5000&timestamp=1499827319559&signature=c8db56825ae71d6d79447849e617115f4a920fa2acdcab2b053c4b2838bd6b71'
string BinanceOrderExecutor::parseOrder(const Order& order) {
    Poco::JSON::Object::Ptr json = new Poco::JSON::Object;

    // Price must be in units of 'quote_increment' product units.
    // For BTC-USD it's 0.01. Therefore, $100 = 10000 units.
    // If we'd like to use multiple coins (likely), we should ask via websocket
    // for 'quote_increment' for each type of coin.
    // TODO: What should be price unit in the 'Order' class?
    // FIXME: Change price value depending on units in 'Order' class.

    string currency = "BTCUSDT";

    string timestamp = generateTimestamp();

    double quantity = 0.005;
    string output;

    output += "symbol=" + currency + "&side=" + (order.isBuyOrder() ? "BUY" : "SELL") + "&type=LIMIT&timeInForce=GTC" + "&quantity=" +
              to_string(quantity) + "&price=" + to_string(order.getPrice()) + "&recvWindow=60000" + "&timestamp=" + timestamp;

    return output;
}

BinanceOrderExecutor::BinanceOrderExecutor() : OrderExecutor() {}

string BinanceOrderExecutor::getURL() {
    // Amend if you are debugging.
    bool debug = false;
    if (debug) {
        return "https://httpbin.org/post";
    } else {
        return "https://testnet.binance.vision/api/v3/order?";
    }
}
string BinanceOrderExecutor::getSecretKey() {
    return "d1CE8YF6bPuOkjUPobN0DMf0NnEX5FrzW4chWQduxMFr412dEsV9c1kCcvRkKNPU"; //this is wrong key
}
string BinanceOrderExecutor::getPublicKey() {
    return "sBe2iw3BTx9bpOofw9ejD5pmAGc7qlVKp3qruGcGbCPtGenVtSEThdeh7WmpPoQq"; //this too
}
string BinanceOrderExecutor::getExchangeName() { return "Binance"; }
