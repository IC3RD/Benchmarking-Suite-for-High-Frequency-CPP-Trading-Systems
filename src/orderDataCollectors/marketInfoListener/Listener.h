#pragma once
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXUserAgent.h>
#include <ixwebsocket/IXWebSocket.h>

#include <json/single_include/nlohmann/json.hpp>
#include <string>

#include "dataManager/OrderBook.h"
#include "orderDataCollectors/OrderDataCollector.h"

class Listener : OrderDataCollector {
 public:
  Listener(std::string url, std::string request,
           Exchange::ExchangeName exchange, OrderBook &orderBook);
  ~Listener(){};
  /* start to listen to incoming data */
  void startListening();
  /* send the message/request to the connected server */
  void sendRequest();

 protected:
  void collectOrderData(OrderTypes::OrderType type, int price, double volume);
  /* Does the exchange specific parsing of json recieved from exchange */
  virtual void passJSON(nlohmann::json json) = 0;
  void setHandlers();
  ix::WebSocket webSocket;
  const std::string url;
  const std::string request;
};
