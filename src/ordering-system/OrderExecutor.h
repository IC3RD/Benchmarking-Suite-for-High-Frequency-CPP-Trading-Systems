#ifndef CPPDESIGNPATTERNSLOWLATENCY_ORDEREXECUTOR_H
#define CPPDESIGNPATTERNSLOWLATENCY_ORDEREXECUTOR_H

#include <Order.h>
#include <OrderBuilder.h>

class OrderExecutor {
public:
  virtual void submitOrder(Order order) = 0;
  static OrderBuilder createOrderBuilder() { return {}; }
  OrderExecutor() = default;
  virtual string getURL() = 0;
  virtual string getExchangeName() = 0;

private:
  virtual string getSecretKey() = 0;
  virtual string getPublicKey() = 0;
};

#endif // CPPDESIGNPATTERNSLOWLATENCY_ORDEREXECUTOR_H
