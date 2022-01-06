#include "OrderDataCollector.h"

#include <memory>

OrderDataCollector::OrderDataCollector(OrderBook& orderBook,
                                       Exchange::ExchangeName exchange)
    : exchange(exchange), orderBook(orderBook) {}

OrderDataCollector::~OrderDataCollector() {}

void OrderDataCollector::constructAndPassOrderData(OrderTypes::OrderType type,
                                                   int price, double volume) {
  std::shared_ptr<OrderData> data =
      std::make_shared<OrderData>(type, exchange, price, volume);
  orderBook.addEntry(data);
}
