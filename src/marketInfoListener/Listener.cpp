#include <iostream>
#include "Listener.h"

Listener::Listener(std::string url, std::string request, std::string exchange) : url(url), request(request), exchange(exchange) {}

void Listener::startListening() {
    webSocket.setUrl(url);
    setHandlers();
    webSocket.start();
}

void Listener::setHandlers() {
    // Setup a callback to be fired (in a background thread,
    // watch out for race conditions !)
    // when a message or an event (open, close, error) is received
    webSocket.setOnMessageCallback([&](const ix::WebSocketMessagePtr& msg)
       {
           if (msg->type == ix::WebSocketMessageType::Message)
           {
               std::cout << "received message from exchange: " << exchange << std::endl;

               using json = nlohmann::json;
               json j = json::parse(msg->str);
               // uncomment to show json from all listeners, to show the listener of a specific exchange put this in an if statement with exchange == "BITMEX"
               //std::cout << std::setw(4) << j << std::endl;
               passJSON(j);
               std::cout << "> " << std::flush;
           }
           else if (msg->type == ix::WebSocketMessageType::Open)
           {
               std::cout << "Connection established to exchange: " << exchange << std::endl;
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

void Listener::sendRequest() {
    webSocket.send(request);
}
