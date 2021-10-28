#pragma once
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>
#include <string>
#include "Listener.h"
#include "../bollingerBand/MarketData.h"

class BitMEXListener: public Listener {
public:
    void startListening();
    void sendRequest(std::string request);
    
private:
    ix::WebSocket webSocket;
    MarketData *data = nullptr;
    const std::string url = "wss://www.bitmex.com/realtime";

    void setHandlers();
};
