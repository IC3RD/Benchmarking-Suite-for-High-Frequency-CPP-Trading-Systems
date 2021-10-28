#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <json/single_include/nlohmann/json.hpp>
#include "BinanceListener.h"

void BinanceListener::startListening() 
{
    webSocket.setUrl(url);
    setHandlers();
    webSocket.start();
}

void BinanceListener::sendRequest(std::string request)
{
    webSocket.send(request);
}

void BinanceListener::setHandlers()
{
    // Setup a callback to be fired (in a background thread,
    // watch out for race conditions !)
    // when a message or an event (open, close, error) is received
    webSocket.setOnMessageCallback([&](const ix::WebSocketMessagePtr& msg)
        {
            if (msg->type == ix::WebSocketMessageType::Message)
            {
                std::cout << "received message: " << std::endl;

                using json = nlohmann::json;
                json j = json::parse(msg->str);
                std::cout << std::setw(4) << j << std::endl;
                std::cout << "> " << std::flush;
            }
            else if (msg->type == ix::WebSocketMessageType::Open)
            {
                std::cout << "Connection established" << std::endl;
                std::cout << "> " << std::flush;
            }
            else if (msg->type == ix::WebSocketMessageType::Error)
            {
                // Maybe SSL is not configured properly
                std::cout << "Connection error: " << msg->errorInfo.reason << std::endl;
                std::cout << "> " << std::flush;
            }
        }
    );
}
