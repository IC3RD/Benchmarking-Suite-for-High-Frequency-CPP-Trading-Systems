#pragma once
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>
#include <string>
#include "Listener.h"

class CoinbaseListener: public Listener {
public:
    void startListening();
    void sendRequest(std::string request);
    
private:
    ix::WebSocket webSocket;
    const std::string url = "wss://ws-feed.exchange.coinbase.com";

    void setHandlers();
};
