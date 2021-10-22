//#include <iostream>
//
//int main() {
//  std::cout << "Hello, World!" << std::endl;
//  return 0;
//}

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <json/single_include/nlohmann/json.hpp>
#include "bollingerBand/BollingerBand.h"
#include "bollingerBand/MarketData.h"

int main()
{

    // Required on Windows
    ix::initNetSystem();

    // Our websocket object
    ix::WebSocket webSocket;

    // Connect to a server with encryption
    // See https://machinezone.github.io/IXWebSocket/usage/#tls-support-and-configuration
    std::string url("wss://www.bitmex.com/realtime");
    webSocket.setUrl(url);

    std::cout << "Connecting to " << url << "..." << std::endl;

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
                //gstd::cout << std::setw(4) << j << std::endl;

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

    // Now that our callback is setup,
    // we can start our background thread and receive messages
    webSocket.start();
    // Display a prompt
    std::cout << "> " << std::flush;

    // sleep for sometime so that message is sent after connection is established
    int wait_unit_ms = 100;
    int waited_ms = 0;
    while (!established)
    {
        waited_ms += wait_unit_ms;
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_unit_ms));
    }
    std::cout << "waited " << waited_ms << " milliseconds" << std::endl;

    // send the request
    webSocket.send("{\"op\":\"subscribe\",\"args\":[\"instrument:XBTUSD\"]}");


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
