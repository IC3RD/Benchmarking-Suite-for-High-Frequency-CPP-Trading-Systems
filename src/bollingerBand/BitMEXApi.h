#include <string>
#include "Order.h"

using namespace std;

class BitMEXApi 
{
    public:
        BitMEXApi(string apiKey, string apiSecret);
        string params(Order order); 
        void placeOrder(Order order);
    private: 
        string domain = "https://testnet.bitmex.com";
        string apiKey;
        string apiSecret;
        string baseURI = "https://testnet.bitmex.com/api/v1";
        
};