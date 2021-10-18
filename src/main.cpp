//#include <iostream>
//
//int main() {
//  std::cout << "Hello, World!" << std::endl;
//  return 0;
//}

#include <BitMEXApi.h>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <json/single_include/nlohmann/json.hpp>

int main()
{
    string bitmexKey = "unkdj30VcxpWe9Yeam8t7mxP";
    string bitmexSecret = "xx3NBrE_qj_TwbWEki3JYEqp2EgMVfQw59bOCMZupYhKs4UD";

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

    // Setup a callback to be fired (in a background thread, watch out for race conditions !)
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
    webSocket.send("{\"op\":\"subscribe\",\"args\":[\"orderBookL2_25:XBTUSD\",\"instrument\"]}");


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

    BitMEXApi bitmex = new BitMEXApi(bitmexKey, bitmexSecret);
 
    return 0;
}
