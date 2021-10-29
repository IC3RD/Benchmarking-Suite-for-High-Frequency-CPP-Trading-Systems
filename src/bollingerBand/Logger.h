#include "BitMEXApi.h"
#include "Order.h"
#include <list>
#include <string>

#pragma once

#define BITMEX_KEY "DQakAekZhCUpMyp8-oBjSZj0"
#define BITMEX_SECRET "_hTVt28pJk094DJI4HBU98V-GsBMiToqqvrOvjUcGhilKuMF"

using namespace std;

class Logger {
public:
  Logger();
  ~Logger();
  void addMessage(string message);
  void logMessage();
  void addOrder(Order order);
  void printAllOrders();

private:
  list<string> *messages;
  list<Order> *orders;
  BitMEXApi bitmex = BitMEXApi(BITMEX_KEY, BITMEX_SECRET);
};
