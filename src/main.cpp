#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXUserAgent.h>
#include <ixwebsocket/IXWebSocket.h>

#include <chrono>
#include <thread>
#include <vector>
#include <iostream>

#include "dataManager/DataManager.h"
#include "marketInfoListener/BinanceListener.h"
#include "marketInfoListener/BitMEXListener.h"
#include "marketInfoListener/CoinbaseListener.h"
#include "marketInfoListener/FTXListener.h"
#include "marketInfoListener/KrakenListener.h"
#include "marketInfoListener/Listener.h"

int main() {
  // Required on Windows
  ix::initNetSystem();

  DataManager centralDataManager;
  std::vector<Listener *> listeners;
  listeners.push_back(new BitMEXListener(centralDataManager));
  //listeners.push_back(new BinanceListener(centralDataManager));
  listeners.push_back(new CoinbaseListener(centralDataManager));
  listeners.push_back(new FTXListener(centralDataManager));
  //listeners.push_back(new KrakenListener(centralDataManager));

  for (Listener *listener : listeners) {
    listener->startListening();
  }

  // set up a thread to check if order needs to be sent after receiving data
  std::thread tOrder(&DataManager::sendOrder, std::ref(centralDataManager));

  std::cout << "> " << std::flush;
  // send the request
  std::this_thread::sleep_for(std::chrono::milliseconds(10000));

  for (Listener *listener : listeners) {
    listener->sendRequest();
  }

  // terminate by pressing enter
  std::string text;
  std::getline(std::cin, text);
  /*
  // Read text from the console and send messages in text mode.
  // Exit with Ctrl-D on Unix or Ctrl-Z on Windows.
  while (std::getline(std::cin, text))
  {
      webSocket.send(text);
      std::cout << "> " << std::flush;
  }
  */
  return 0;
}
