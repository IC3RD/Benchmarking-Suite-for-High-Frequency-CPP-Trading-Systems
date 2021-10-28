#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>
#include <iostream>
#include <string>
#include <json/single_include/nlohmann/json.hpp>
#include "../bollingerBand/BollingerBand.h"
#include "BitMEXListener.h"

void BitMEXListener::startListening()
{
    webSocket.setUrl(url);
    setHandlers();
    webSocket.start();
}

void BitMEXListener::sendRequest(std::string request)
{
    webSocket.send(request);
}

void BitMEXListener::setHandlers()
{
    // Setup a callback to be fired (in a background thread,
    // watch out for race conditions !)
    // when a message or an event (open, close, error) is received
    webSocket.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg)
        {
            if (msg->type == ix::WebSocketMessageType::Message)
            {
                std::cout << "received message: " << std::endl;

                using json = nlohmann::json;
                json j = json::parse(msg->str);

                if (j.contains("data")) {
                    if (!data) {
                        data = new MarketData("Bitcoin", j.at("data")[0].at("askPrice"), j.at("data")[0].at("bidPrice"), j.at("data")[0].at("volume"));
                        data->newMarketData();
                    } else {
                        if (j.at("data")[0].contains("askPrice")) {
                            data->updateSell(j.at("data")[0].at("askPrice"));
                            data->newMarketData();
                        }
                        if (j.at("data")[0].contains("bidPrice")) {
                            data->updateBuy(j.at("data")[0].at("bidPrice"));
                            data->newMarketData();
                        }
                        if (j.at("data")[0].contains("volume")) {
                            data->updateVolume(j.at("data")[0].at("volume"));
                            data->newMarketData();
                        }
                    }
                }

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
