#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXUserAgent.h>
#include <ixwebsocket/IXWebSocket.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "dataManager/OrderBook.h"
#include "exchange/Exchange.h"
#include "orderDataCollectors/marketInfoListener/BinanceListener.h"
#include "orderDataCollectors/marketInfoListener/BitMEXListener.h"
#include "orderDataCollectors/marketInfoListener/CoinbaseListener.h"
#include "orderDataCollectors/marketInfoListener/FTXListener.h"
#include "orderDataCollectors/marketInfoListener/KrakenListener.h"
#include "orderDataCollectors/marketInfoListener/Listener.h"
#include "tradingStrategies/bollingerBand/BollingerBand.h"

int main() {
  // Required on Windows
  ix::initNetSystem();

  // Set up order books for each exchange

  std::shared_ptr<OrderBook> binanceOrderBook =
      std::make_shared<OrderBook>(Exchange::BINANCE);
  std::shared_ptr<OrderBook> coinbaseOrderBook =
      std::make_shared<OrderBook>(Exchange::COINBASE);
  std::shared_ptr<OrderBook> krakenOrderBook =
      std::make_shared<OrderBook>(Exchange::KRAKEN);

  // initialise shared trading strategy
  std::shared_ptr<BollingerBand> strategy = std::make_shared<BollingerBand>();

  strategy->insertNewOrderBook(binanceOrderBook);
  strategy->insertNewOrderBook(coinbaseOrderBook);
  strategy->insertNewOrderBook(krakenOrderBook);

  // Some bollinger band specific additions
  strategy->addExchange(Exchange::BINANCE);
  strategy->addExchange(Exchange::COINBASE);
  strategy->addExchange(Exchange::KRAKEN);

  // add shared trading strategy to each order book
  binanceOrderBook->addTradingStrategy(strategy);
  coinbaseOrderBook->addTradingStrategy(strategy);
  krakenOrderBook->addTradingStrategy(strategy);

  // initialise the listeners for the exchange
  std::vector<Listener *> listeners;
  // listeners.push_back(
  //  new BitMEXListener(centralDataManager, bitmexOrderBook));
  listeners.push_back(new BinanceListener(*binanceOrderBook));
  listeners.push_back(new CoinbaseListener(*coinbaseOrderBook));
  // listeners.push_back(new FTXListener(centralDataManager, orderBook));
  listeners.push_back(new KrakenListener(*krakenOrderBook));

  for (Listener *listener : listeners) {
    listener->startListening();
  }

  // set up a thread to check if order needs to be sent after receiving data
  // std::thread tOrder(&DataManager::sendOrder, std::ref(centralDataManager));

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
