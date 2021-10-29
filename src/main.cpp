#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXUserAgent.h>
#include <ixwebsocket/IXWebSocket.h>

#include <chrono>
#include <thread>
#include <vector>
#include "marketInfoListener/Listener.h"
#include "marketInfoListener/BitMEXListener.h"
#include "marketInfoListener/BinanceListener.h"
#include "marketInfoListener/CoinbaseListener.h"
#include "marketInfoListener/FTXListener.h"
#include "marketInfoListener/KrakenListener.h"

int main()
{
    // Required on Windows
    ix::initNetSystem();

    std::vector<Listener*> listeners;
    listeners.push_back(new BitMEXListener());
    listeners.push_back(new BinanceListener());
    listeners.push_back(new CoinbaseListener());
    listeners.push_back(new FTXListener());
    listeners.push_back(new KrakenListener());

    for (Listener *listener : listeners)
    {
        listener->startListening();
    }

    std::cout << "> " << std::flush;
    // send the request
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    for (Listener *listener : listeners)
    {
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
  });

  // Now that our callback is setup,
  // we can start our background thread and receive messages
  webSocket.start();
  // Display a prompt
  std::cout << "> " << std::flush;

  // sleep for sometime so that message is sent after connection is established
  int wait_unit_ms = 100;
  int waited_ms = 0;
  while (!established) {
    waited_ms += wait_unit_ms;
    std::this_thread::sleep_for(std::chrono::milliseconds(wait_unit_ms));
  }
  std::cout << "waited " << waited_ms << " milliseconds" << std::endl;

  // send the request
  webSocket.send("{\"op\":\"subscribe\",\"args\":[\"instrument:XBTUSD\"]}");

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
