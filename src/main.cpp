#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXUserAgent.h>
#include <ixwebsocket/IXWebSocket.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "exchange/Exchange.h"
#include "dataManager/DataManager.h"
#include "dataManager/OrderBook.h"
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
  // Set up order books for each exchange
  OrderBook binanceOrderBook(Exchange::BINANCE);
  OrderBook coinbaseOrderBook(Exchange::COINBASE);

  // initialise shared trading strategy
  std::shared_ptr<BollingerBand> strategy = std::make_shared<BollingerBand>(100);

  // add shared trading strategy to each order book
  binanceOrderBook.addTradingStrategy(strategy);
  coinbaseOrderBook.addTradingStrategy(strategy);

  // initialise the listeners for the exchange
  std::vector<Listener *> listeners;
  //listeners.push_back(new BitMEXListener(centralDataManager, orderBook));
  listeners.push_back(new BinanceListener(centralDataManager, binanceOrderBook));
  listeners.push_back(new CoinbaseListener(centralDataManager, coinbaseOrderBook));
  //listeners.push_back(new FTXListener(centralDataManager, orderBook));
  //listeners.push_back(new KrakenListener(centralDataManager));

  for (Listener *listener : listeners) {
    listener->startListening();
  }

  // set up a thread to check if order needs to be sent after receiving data
  //std::thread tOrder(&DataManager::sendOrder, std::ref(centralDataManager));

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
