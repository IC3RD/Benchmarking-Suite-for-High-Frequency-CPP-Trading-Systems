#include "marketInfoListener/BinanceListener.h"
#include "marketInfoListener/BitMEXListener.h"
#include "marketInfoListener/CoinbaseListener.h"
#include "marketInfoListener/FTXListener.h"
#include "marketInfoListener/KrakenListener.h"
#include "marketInfoListener/Listener.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXUserAgent.h>
#include <ixwebsocket/IXWebSocket.h>
#include <thread>
#include <vector>

int main() {
  // Required on Windows
  ix::initNetSystem();

  std::vector<Listener *> listeners;
  listeners.push_back(new BitMEXListener());
  listeners.push_back(new BinanceListener());
  listeners.push_back(new CoinbaseListener());
  listeners.push_back(new FTXListener());
  listeners.push_back(new KrakenListener());

  for (Listener *listener : listeners) {
    listener->startListening();
  }

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
