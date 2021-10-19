#include <deque>
#include <math.h>
#include <iostream>
#include "BitMEXApi.h"
#include <curl/curl.h>

using namespace std;

BitMEXApi::BitMEXApi(string apiKey, string apiSecret)
    : apiKey(apiKey), apiSecret(apiSecret) {};

void BitMEXApi::placeOrder(Order order){
    string postRequest = " /api/v1/order " + params(order);
    cout << postRequest << "\n";
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl){
        curl_easy_setopt(curl, CURLOPT_URL, "https://testnet.bitmex.com/api/v1/order");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "symbol=XBTUSD&price=62195&ordType=buy&volume=1");
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
 
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
}

string BitMEXApi::params(Order order){
    string params = "{";
    return params + "\"symbol\": \"" + order.getSymbol() + "\", "
           + "\"price\": " + to_string(order.getPrice()) + ", "
           + "\"volume\": " + to_string(order.getVolume()) + "}";
}