#pragma once
#include <OrderExecutor.h>
#include <exchange/Order.h>

class ExchangeOrderExecutor : public OrderExecutor {
    public:
        ExchangeOrderExecutor() = default;
        void submitOrder(Order order) override;
        std::string getDestination();
        virtual std::string getExchangeName() = 0;

    private:
        virtual std::string getSecretKey() = 0;
        virtual std::string getPublicKey() = 0;
};