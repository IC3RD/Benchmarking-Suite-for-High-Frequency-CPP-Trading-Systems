#pragma once

#include <stdio.h>
#include "../dataManager/DataManager.h"
#include "../ordering-system/OrderExecutor.h"
#include <string>

using namespace std;

class TradingStrategy {
    public:
        TradingStrategy();
        ~TradingStrategy();
        void updateData(MarketData&);
        virtual void runStrategy() = 0;
        virtual void buy(MarketData&);
        virtual void sell(MarketData&);
    protected:
        unordered_map<Exchange::ExchangeName, MarketData&> exchangeData;
        OrderExecutor *orderExecutor;
};