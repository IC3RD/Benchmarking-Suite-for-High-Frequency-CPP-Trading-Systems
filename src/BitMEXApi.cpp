#include <deque>
#include <math.h>
#include <iostream>
#include "BitMEXApi.h";

using namespace std;

BitMEXApi::BitMEXApi(string apiKey, string apiSecret)
{
    apiKey = apiKey;
    apiSecret = apiSecret;
}

string BitMEXApi::placeOrder(Order order){
    cout << "Test";
}

string BitMEXApi::params(Order order){
    string params = "{ ";
    params + "\"symbol\" : \"" + order.getSymbol() + "\","
           + "\"price\" : \"" + to_string(order.getPrice()) + "\","
           + "\"volume\" : \"" + to_string(order.getVolume()) + "\"," 
           + " }";
}