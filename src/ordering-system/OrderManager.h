#ifndef CPPDESIGNPATTERNSLOWLATENCY_ORDERMANAGER_H
#define CPPDESIGNPATTERNSLOWLATENCY_ORDERMANAGER_H

#include <Order.h>
#include <OrderBuilder.h>

class OrderManager {
public:
    virtual void createOrder(Order order);

    virtual void submitOrder(Order order);

    virtual OrderBuilder createOrderBuilder();
};


#endif //CPPDESIGNPATTERNSLOWLATENCY_ORDERMANAGER_H
