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

string BitMEXApi::query(){
    cout << "Test";
}