#ifndef CPPDESIGNPATTERNSLOWLATENCY_BITMEXORDERMANAGER_H
#define CPPDESIGNPATTERNSLOWLATENCY_BITMEXORDERMANAGER_H

#include <OrderManager.h>
class BitmexOrderManager : public OrderManager {
public:
  BitmexOrderManager();
  void submitOrder(Order order) override;
  string getURL() override;
  string getExchangeName() override;

private:
  string getSecretKey() override;
  string getPublicKey() override;
  void generateHeaders(struct curl_slist **chunk, const string &data);
  static string parseOrder(const Order &order);
  static string generateTimestamp();
  string generateSignature(const string &message, const string &timestamp);
};

#endif // CPPDESIGNPATTERNSLOWLATENCY_BITMEXORDERMANAGER_H
