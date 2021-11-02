//
// Created by panos on 10/29/21.
//

#ifndef CPPDESIGNPATTERNSLOWLATENCY_BINANCEORDERMANAGER_H
#define CPPDESIGNPATTERNSLOWLATENCY_BINANCEORDERMANAGER_H

#include <OrderBuilder.h>
#include <OrderManager.h>

class BinanceOrderManager : public OrderManager {
public:
    BinanceOrderManager();
    void submitOrder(Order order) override;
    string getURL() override;
    string getExchangeName() override;

private:
    string parseOrder(const Order& order);
    string authenticate(string message);
    string generateTimestamp();
    void generateHeaders(struct curl_slist **chunk);
    string getSecretKey() override;
    string getPublicKey() override;

};

#endif //CPPDESIGNPATTERNSLOWLATENCY_BINANCEORDERMANAGER_H
