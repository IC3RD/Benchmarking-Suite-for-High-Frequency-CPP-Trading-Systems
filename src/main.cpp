#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <vector>
#include "marketInfoListener/Listener.h"
#include "marketInfoListener/BitMEXListener.h"
#include "marketInfoListener/BinanceListener.h"
#include "marketInfoListener/CoinbaseListener.h"
#include "marketInfoListener/FTXListener.h"
#include "marketInfoListener/KrakenListener.h"

int main()
{

    // Required on Windows
    ix::initNetSystem();

    std::vector<Listener*> listeners;
    listeners.push_back(new BitMEXListener());
    listeners.push_back(new BinanceListener());
    listeners.push_back(new CoinbaseListener());
    listeners.push_back(new FTXListener());
    listeners.push_back(new KrakenListener());

    // BitMEXListener bitmexListener;
    // bitmexListener.startListening();
    // BinanceListener binanceListener;
    // binanceListener.startListening();

    for (auto listener : listeners)
    {
        listener->startListening();
    }

    /*
    // Our websocket object
    ix::WebSocket webSocket;
    ix::WebSocket webSocket2;

    // Connect to a server with encryption
    // See https://machinezone.github.io/IXWebSocket/usage/#tls-support-and-configuration
    std::string url("wss://www.bitmex.com/realtime");
    webSocket.setUrl(url);

    // Connect to a server with encryption
    std::string url2("wss://stream.binance.com:9443/ws/bnbbtc@depth");
    webSocket2.setUrl(url2);

    std::cout << "Connecting to " << url << "..." << std::endl;
    std::cout << "Connecting to " << url2 << "..." << std::endl;

    bool established = false;

    MarketData *data = nullptr;

    // Setup a callback to be fired (in a background thread, watch out for race conditions !)
    // when a message or an event (open, close, error) is received
    webSocket.setOnMessageCallback([&](const ix::WebSocketMessagePtr& msg)
        {
            if (msg->type == ix::WebSocketMessageType::Message)
            {
                std::cout << "received message: " << std::endl;

                using json = nlohmann::json;
                json j = json::parse(msg->str);
                // std::cout << std::setw(4) << j << std::endl;

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
                established = true;
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

    webSocket2.setOnMessageCallback([&](const ix::WebSocketMessagePtr& msg)
        {
            if (msg->type == ix::WebSocketMessageType::Message)
            {
                std::cout << "received message: " << std::endl;

                using json = nlohmann::json;
                json j = json::parse(msg->str);
                std::cout << std::setw(4) << j << std::endl;
                /*
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
                */
                /*

                std::cout << "> " << std::flush;
            }
            else if (msg->type == ix::WebSocketMessageType::Open)
            {
                established = true;
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

    // Now that our callback is setup,
    // we can start our background thread and receive messages
    webSocket.start();
    webSocket2.start();

    // sleep for sometime so that message is sent after connection is established
    int wait_unit_ms = 100;
    int waited_ms = 0;
    while (!established)
    {
        waited_ms += wait_unit_ms;
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_unit_ms));
    }
    std::cout << "waited " << waited_ms << " milliseconds" << std::endl;
    */ 
    // Display a prompt
    std::cout << "> " << std::flush;

    // send the request
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    listeners[0]->sendRequest("{\"op\":\"subscribe\",\"args\":[\"instrument:XBTUSD\"]}");
    listeners[2]->sendRequest("{\"type\": \"subscribe\", \"product_ids\": [\"BTC-USD\"], \"channels\": [\"ticker\"]}");
    listeners[3]->sendRequest("{\"op\": \"subscribe\", \"channel\": \"trades\", \"market\": \"BTC-PERP\"}");
    listeners[4]->sendRequest("{\"event\":\"subscribe\", \"subscription\":{\"name\":\"ticker\"}, \"pair\":[\"BTC/USD\"]}");


    // terminate by pressing enter
    std::string text;
    std::getline(std::cin, text);
    /*
    // Read text from the console and send messages in text mode.
    // Exit with Ctrl-D on Unix or Ctrl-Z on Windows.
    while (std::getline(std::cin, text))
    {
        webSocket.send(text);
        std::cout << "> " << std::flush;
    }
    */
    return 0;
}
