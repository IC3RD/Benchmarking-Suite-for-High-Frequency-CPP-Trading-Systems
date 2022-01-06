#include "Band.h"

#include <math.h>

Band::Band() {
  meanPrice = 0;
  stdDeviation = 0;
  noOfElements = 0;
}

Band::~Band() {}

long long Band::getMean() { return meanPrice; }

long long Band::getStd() { return stdDeviation; }

int Band::getNoOfElements() { return noOfElements; }

void Band::insertNewData(long price, std::shared_ptr<OrderBook> book) {
  if (book->hasAsks()) {
    if (price > book->getLowestAsk()->getOrderPrice() + stdDeviation) {
      return;
    }
  }
  if (book->hasBids()) {
    if (price < book->getHighestBid()->getOrderPrice() - stdDeviation) {
      return;
    }
  }

  long long newMean = (meanPrice * noOfElements + price) / (noOfElements + 1);
  long long delta = newMean - meanPrice;
  int newNoOfElements = noOfElements + 1;
  long long newVar = ((price - newMean) * (price - newMean) / newNoOfElements) +
                (noOfElements / newNoOfElements) *
                    ((stdDeviation * stdDeviation) + (delta * delta));
  meanPrice = newMean;
  stdDeviation = sqrt(newVar);
  noOfElements = newNoOfElements;
}