#include <stdio.h>

#include <iostream>

#include "BollingerBand.h"
#include "MarketData.h"

int main() {
  MarketData *data = new MarketData("Bitcoin", 4, 2, 10);
  BollingerBand *band = data->getStrategy();

  std::cout << "Price is " << data->getPrice() << std::endl;
  std::cout << "Volume is " << data->getVolume() << std::endl;
  std::cout << "Symbol is " << data->getSymbol() << std::endl;
  data->newMarketData();

  data->updateBuy(5);
  data->updateSell(3);
  data->newMarketData();

  data->updateBuy(6);
  data->updateSell(4);
  data->newMarketData();

  std::cout << "Curr moving average is " << band->getCurrMovingAverage()
            << std::endl;
  std::cout << "Curr std dev is " << band->getCurrStdDeviation() << std::endl;
  return 0;
}
