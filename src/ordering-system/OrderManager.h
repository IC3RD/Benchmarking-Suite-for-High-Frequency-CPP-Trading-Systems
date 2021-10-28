#ifndef CPPDESIGNPATTERNSLOWLATENCY_ORDERMANAGER_H
#define CPPDESIGNPATTERNSLOWLATENCY_ORDERMANAGER_H

#include <Order.h>
#include <OrderBuilder.h>

class OrderManager {
public:
    virtual void submitOrder(Order order) = 0;

    OrderBuilder createOrderBuilder() {
      return {};
    }

    OrderManager() = default;
};


#endif //CPPDESIGNPATTERNSLOWLATENCY_ORDERMANAGER_H
