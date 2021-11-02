#ifndef CPPDESIGNPATTERNSLOWLATENCY_BITMEXORDEREXECUTOR_H
#define CPPDESIGNPATTERNSLOWLATENCY_BITMEXORDEREXECUTOR_H

#include <OrderExecutor.h>
class BitmexOrderExecutor : public OrderExecutor {
public:
  BitmexOrderExecutor();
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

#endif // CPPDESIGNPATTERNSLOWLATENCY_BITMEXORDEREXECUTOR_H
