#ifndef CPPDESIGNPATTERNSLOWLATENCY_ORDERBUILDER_H
#define CPPDESIGNPATTERNSLOWLATENCY_ORDERBUILDER_H

#include "../exchange/Order.h"

class OrderBuilder {
public:
  OrderBuilder();

  void createBuyOrder(int price);

  void createSellOrder(int price);

  void addLimit(int limit);

  void amendPrice(int newPrice);

  void amendVolume(int volume);

  Order toOrder() const {
    return {"implement this", price, volume, isBuyOrder};
  }

private:
  bool isBuyOrder;
  int limit;
  int price;
  int volume;
};

#endif // CPPDESIGNPATTERNSLOWLATENCY_ORDERBUILDER_H
