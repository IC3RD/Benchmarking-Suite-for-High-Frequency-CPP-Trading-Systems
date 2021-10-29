#include <iostream>
#include <iomanip>
#include <string>
#include <json/single_include/nlohmann/json.hpp>
#include "KrakenListener.h"

KrakenListener::KrakenListener() : Listener("wss://ws.kraken.com/", "{\"event\":\"subscribe\", \"subscription\":{\"name\":\"ticker\"}, \"pair\":[\"BTC/USD\"]}", "KRAKEN") {}

// reference: https://docs.kraken.com/websockets/#message-ticker
void KrakenListener::passJSON(nlohmann::json json) {
    // Have to do weird checking since the second json element is anonymous
    if (json.contains("connectionID")) {
        //std::cout << "contains connection";
    } else if (json.contains("event") && json.at("event") == "heartbeat"){
        //std::cout << "heartbeat";
    } else if (!json.contains("channelID")){
        auto &askPrice = json[1].at("a")[0];
        int askVolume = json[1].at("a")[1];
        auto &bidPrice = json[1].at("b")[0];
        int bidVolume = json[1].at("b")[1];
    }
}
