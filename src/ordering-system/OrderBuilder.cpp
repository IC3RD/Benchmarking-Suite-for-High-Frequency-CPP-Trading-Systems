#include "OrderBuilder.h"

void OrderBuilder::addLimit(int limit) {
    this->limit = limit;
}

void OrderBuilder::amendVolume(int volume) {
  this->volume = volume;
}

void OrderBuilder::createBuyOrder(int price) {
    this->isBuyOrder = true;
    this->price = price;
}

void OrderBuilder::createSellOrder(int price) {
    this->isBuyOrder = false;
    this->price = price;
}

void OrderBuilder::amendPrice(int newPrice) {
    this->price = newPrice;
}

OrderBuilder::OrderBuilder() {
    this->price = 0;
    this->isBuyOrder = false;
    this->limit = -1;
}
