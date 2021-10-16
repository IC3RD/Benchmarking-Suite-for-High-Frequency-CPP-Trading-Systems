//#include <iostream>
//
//int main() {
//  std::cout << "Hello, World!" << std::endl;
//  return 0;
//}

/*
 *  main.cpp
 *  Author: Benjamin Sergeant
 *  Copyright (c) 2020 Machine Zone, Inc. All rights reserved.
 *
 *  Super simple standalone example. See ws folder, unittest and doc/usage.md for more.
 *
 *  On macOS
 *  $ mkdir -p build ; (cd build ; cmake -DUSE_TLS=1 .. ; make -j ; make install)
 *  $ clang++ --std=c++11 --stdlib=libc++ main.cpp -lixwebsocket -lz -framework Security -framework Foundation
 *  $ ./a.out
 *
 *  Or use cmake -DBUILD_DEMO=ON option for other platforms
 */

#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>
#include <iostream>
#include <chrono>
#include <thread>

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

    // Setup a callback to be fired (in a background thread, watch out for race conditions !)
    // when a message or an event (open, close, error) is received
    webSocket.setOnMessageCallback([&](const ix::WebSocketMessagePtr& msg)
        {
            if (msg->type == ix::WebSocketMessageType::Message)
            {
                std::cout << "received message: " << msg->str << std::endl;
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

    return 0;
}
