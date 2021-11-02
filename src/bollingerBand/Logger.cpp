#include "Logger.h"
#include <iostream>
#include <string>

Logger::Logger() {
  messages = new std::list<std::string>();
  orders = new std::list<Order>();
}

Logger::~Logger() {
  delete messages;
  delete orders;
}

// optimise to store these and then print on command when out of the hotpath
void Logger::addMessage(std::string message) { messages->push_back(message); }

void Logger::logMessage() {
  std::cout << messages->front() << std::endl;
  messages->pop_front();
}

void Logger::addOrder(Order order) {
  orders->push_front(order);

  bitmex.placeOrder(order);
}

void Logger::printAllOrders() {
  for (Order o : *orders) {
    std::string buyOrSell = o.isBuyOrder() ? "Buy" : "Sell";
    std::cout << "OrderType: " + buyOrSell + " Symbol: " + o.getSymbol() +
                     " Price: " + std::to_string(o.getPrice()) +
                     " Volume: " + std::to_string(o.getVolume());
  }
  std::cout << "All orders printed";
}
