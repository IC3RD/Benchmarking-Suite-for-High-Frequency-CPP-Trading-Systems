#include <deque>
#include <math.h>
#include <iostream>
#include "BitMEXApi.h"
#include <curl/curl.h>
#include "SHA256Engine.h"
#include <Poco/HMACEngine.h>
#include <Poco/SHA2Engine.h>

using namespace std;

BitMEXApi::BitMEXApi(string apiKey, string apiSecret)
        : apiKey(apiKey), apiSecret(apiSecret) {};

// Adds necessary header files to curl request. See: https://www.bitmex.com/app/apiKeysUsage
void BitMEXApi::authenticate(CURL *curl, struct curl_slist **chunk) {
    // Per the bitmex documentation, we need to configure the following headers.
    // 1. configure api-expires. i.e. add timestamp in seconds when authentication no longer valid.
    // 2. add api-key
    // 3. add api-signature = hex(HMAC_SHA256(apiSecret, verb + path + expires + data))


    /* Generating the api-expires header.*/
    // The amount of time authentication lasts for in seconds. I (Jake) have set this to 30 minutes. Should it last
    // for the entire trading day?
    long api_duration = 1800;

    // Get the UNIX timestamp of the expiry time.
    const auto time = std::chrono::system_clock::now();
    const auto current_time = std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count();
    auto expiry_time = current_time + api_duration;

    cout << "expiry_time:" << to_string(expiry_time) << '\n';

    string api_expires_header = "api-expires:" + std::to_string(expiry_time);

    *chunk = curl_slist_append(*chunk, api_expires_header.c_str());

    /* Generating the api-key header.*/
    string api_key_header = "api-key:" + this->apiKey;

    *chunk = curl_slist_append(*chunk, api_key_header.c_str());

    /* Generating the api-signature header.*/
    SHA256Engine engine{};
    string verb = "POST";
    string path = "/api/v1/order";
    long expires = expiry_time;
    // A test order (copied from API page). Later, this function will take in a market order and generate data.
    string data = "{\"symbol\":\"XBTUSD\"}";

    // Yes, this is the only reason we need Poco....fml.
    Poco::HMACEngine<SHA256Engine> hmac{this->apiSecret};
    hmac.update(verb + path + to_string(expires) + data);

    string hmac_hex = Poco::DigestEngine::digestToHex(hmac.digest());

    string api_signature_header = "api-signature:" + hmac_hex;

    *chunk = curl_slist_append(*chunk, api_signature_header.c_str());

    //test
    string test_api_secret = "chNOOS4KvNXR_Xq4k4c9qsfoKWvnDecLATCRlcBwyKDYnWgO";
    string test_verb = "GET";
    string test_path = "/api/v1/instrument";
    int test_expires = 1518064236;
    string test_data = "";

//    Poco::HMACEngine<SHA256Engine> test_hmac{test_api_secret.c_str()};
//    hmac.update((test_verb + test_path + to_string(test_expires) + test_data).c_str());
    Poco::HMACEngine<SHA256Engine> test_hmac{"chNOOS4KvNXR_Xq4k4c9qsfoKWvnDecLATCRlcBwyKDYnWgO"};
    hmac.update("GET/api/v1/instrument1518064236");


    cout << "TEST SIGNATURE: " << Poco::DigestEngine::digestToHex(test_hmac.digest()) << "\n";



}

void BitMEXApi::placeOrder(Order order) {
    string postRequest = " /api/v1/order " + params(order);
    cout << postRequest << "\n";
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        // I think this is now done in the authenticate function, the order is encoded in the api-signature.
        // Pls message me if not - Jake
        //        curl_easy_setopt(curl, CURLOPT_URL, "https://testnet.bitmex.com/api/v1/order");
        //        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "symbol=XBTUSD&price=62195&ordType=buy&volume=1");

        // Add the required headers.
        struct curl_slist *chunk = NULL;
        BitMEXApi::authenticate(curl, &chunk);

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_URL, "https://testnet.bitmex.com/api/v1");

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
}

string BitMEXApi::params(Order order) {
    string params = "{";
    return params + "\"symbol\": \"" + order.getSymbol() + "\", "
           + "\"price\": " + to_string(order.getPrice()) + ", "
           + "\"volume\": " + to_string(order.getVolume()) + "}";
}