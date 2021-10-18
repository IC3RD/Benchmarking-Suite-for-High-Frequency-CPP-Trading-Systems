#include <iostream>
#include <string>
#include "Logger.h"

using namespace std;

Logger::Logger() {
  messages = new list<string>();
  orders = new list<Order>();
}

Logger::~Logger() {
  delete messages;
  delete orders;
}

//optimise to store these and then print on command when out of the hotpath
void Logger::addMessage(string message) {
  messages->push_back(message);
}

void Logger::logMessage() {
  cout << messages->front() << "\n";
  messages->pop_front();
}

void Logger::addOrder(Order order) {
  orders->push_front(order);
}

void Logger::printAllOrders() {
  for (Order o : orders){
    cout << "OrderType: " << o.isBuy ? "Buy" : "Sell" << " Symbol: " << o.getSymbol << " Price: " 
         << o.getPrice << " Volume: " << o.getVolume;
  }
  cout << "All orders printed";
}

