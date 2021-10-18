#include <string>

using namespace std;

class BitMEXApi 
{
    public:
        BitMEXApi(string apiKey, string apiSecret)

    private: 
        string domain = "https://testnet.bitmex.com";
        string apiKey;
        string apiSecret;
        string query();
        
};