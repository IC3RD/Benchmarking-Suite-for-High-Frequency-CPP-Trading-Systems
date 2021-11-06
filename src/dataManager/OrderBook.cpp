#pragma once

#include "OrderBook.h"

#include "bollingerBand/BollingerBand.h"

OrderBook::OrderBook() {
    listenerStrategies.push_back(std::make_unique<BollingerBand>(100));
    // these separate stores are causes errors for now
    //bidStore = std::make_unique<OrderDataStore>();
    //askStore = std::make_unique<OrderDataStore>();
}

OrderBook::~OrderBook() {}

void OrderBook::addEntry(OrderData data) {
    switch (data.getOrderType()) {
        case (OrderTypes::ASK):
            askStore->addEntry(data);
        case (OrderTypes::BID):
            bidStore->addEntry(data);
    }
}

void OrderBook::sendOrder() {
    askStore->sendOrder();
    bidStore->sendOrder();
}