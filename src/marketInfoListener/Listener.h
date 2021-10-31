#pragma once
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXUserAgent.h>
#include <ixwebsocket/IXWebSocket.h>

#include <json/single_include/nlohmann/json.hpp>
#include <string>

#include "dataManager/DataManager.h"

class Listener {
 public:
  Listener(std::string url, std::string request, std::string exchange,
           DataManager &dataManager);
  ~Listener(){};
  /* start to listen to incoming data */
  void startListening();
  /* send the message/request to the connected server */
  void sendRequest();

 protected:
  /* Does the exchange specific parsing of json recieved from exchange */
  virtual void passJSON(nlohmann::json json) = 0;
  /* set up callback/thread to react to incoming data */
  void setHandlers();
  ix::WebSocket webSocket;
  const std::string url;
  const std::string request;
  const std::string exchange;

 private:
  DataManager jcentralDataManager;
};
