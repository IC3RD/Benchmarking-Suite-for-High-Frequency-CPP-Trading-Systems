#ifndef CPPDESIGNPATTERNSLOWLATENCY_ORDERMANAGER_H
#define CPPDESIGNPATTERNSLOWLATENCY_ORDERMANAGER_H

#include <Order.h>
#include <OrderBuilder.h>

class OrderManager {
public:
  virtual void submitOrder(Order order) = 0;
  static OrderBuilder createOrderBuilder() { return {}; }
  OrderManager() = default;
  virtual string getURL() = 0;
  virtual string getExchangeName() = 0;

private:
  virtual string getSecretKey() = 0;
  virtual string getPublicKey() = 0;
};

#endif // CPPDESIGNPATTERNSLOWLATENCY_ORDERMANAGER_H
