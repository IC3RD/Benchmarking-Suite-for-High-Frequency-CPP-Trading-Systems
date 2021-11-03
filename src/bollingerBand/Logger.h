#pragma once
#include <list>
#include <string>

#include "BitMEXApi.h"
#include "Order.h"

#define BITMEX_KEY "DQakAekZhCUpMyp8-oBjSZj0"
#define BITMEX_SECRET "_hTVt28pJk094DJI4HBU98V-GsBMiToqqvrOvjUcGhilKuMF"

class Logger {
 public:
  Logger();
  ~Logger();
  void addMessage(std::string message);
  void logMessage();
  void addOrder(Order order);
  void printAllOrders();

 private:
  std::list<std::string> *messages;
  std::list<Order> *orders;
  BitMEXApi bitmex = BitMEXApi(BITMEX_KEY, BITMEX_SECRET);
};
