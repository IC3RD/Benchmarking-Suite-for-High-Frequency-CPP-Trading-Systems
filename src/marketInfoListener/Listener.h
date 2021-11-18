#pragma once
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXUserAgent.h>
#include <ixwebsocket/IXWebSocket.h>

#include <json/single_include/nlohmann/json.hpp>
#include <string>

#include "../exchange/Exchange.h"
#include "dataManager/OrderBook.h"
#include "exchange/OrderData.h"
#include "exchange/OrderTypes.h"

class Listener {
 public:
  Listener(std::string url, std::string request,
           Exchange::ExchangeName exchange, OrderBook &orderBook);
  ~Listener(){};
  /* start to listen to incoming data */
  void startListening();
  /* send the message/request to the connected server */
  void sendRequest();

 protected:
  /* Does the exchange specific parsing of json recieved from exchange */
  virtual void passJSON(nlohmann::json json) = 0;

  void constructAndPassOrderData(OrderTypes::OrderType type, int price,
                                 double volume);

  void setHandlers();
  ix::WebSocket webSocket;
  const std::string url;
  const std::string request;
  const Exchange::ExchangeName exchange;

 private:
  OrderBook &orderBook;
};
