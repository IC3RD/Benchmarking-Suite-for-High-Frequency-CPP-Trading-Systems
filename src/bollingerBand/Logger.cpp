#include "Logger.h"
#include <iostream>
#include <string>

using namespace std;

Logger::Logger() {
  messages = new list<string>();
  orders = new list<Order>();
}

Logger::~Logger() {
  delete messages;
  delete orders;
}

// optimise to store these and then print on command when out of the hotpath
void Logger::addMessage(string message) { messages->push_back(message); }

void Logger::logMessage() {
  cout << messages->front() << "\n";
  messages->pop_front();
}

void Logger::addOrder(Order order) {
  orders->push_front(order);

  bitmex.placeOrder(order);
}

void Logger::printAllOrders() {
  for (Order o : *orders) {
    string buyOrSell = o.isBuyOrder() ? "Buy" : "Sell";
    cout << "OrderType: " + buyOrSell + " Symbol: " + o.getSymbol() +
                " Price: " + to_string(o.getPrice()) +
                " Volume: " + to_string(o.getVolume());
  }
  cout << "All orders printed";
}
