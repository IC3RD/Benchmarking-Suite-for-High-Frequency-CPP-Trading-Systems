#include "OrderManager.h"

#include "exchange/Exchange.h"
#include "ordering-system/utils/dotenv.h"

OrderManager::OrderManager() {
  std::string path{std::getenv("HOME")};
  path += "/API-KEYS.env";
  dotenv::init(path.c_str());
  orderExecutors[Exchange::BINANCE] =
      new BinanceOrderExecutor(dotenv::getenv("BINANCE_API_SECRET"),
                               dotenv::getenv("BINANCE_API_PUBLIC"));
  orderExecutors[Exchange::BITMEX] = new BitmexOrderExecutor(
      dotenv::getenv("BITMEX_API_SECRET"), dotenv::getenv("BITMEX_API_PUBLIC"));
  orderExecutors[Exchange::COINBASE] =
      new CoinbaseOrderExecutor(dotenv::getenv("COINBASE_API_SECRET"),
                                dotenv::getenv("COINBASE_API_PUBLIC"));

  portfolio = new std::vector<Order>();
}

void OrderManager::submitOrder(Exchange::ExchangeName exchange,
                               const Order& order) {
  OrderExecutor* executor = orderExecutors.at(exchange);
  executor->enableOutput();
  executor->submitOrder(order);
  portfolio->push_back(order);
}
