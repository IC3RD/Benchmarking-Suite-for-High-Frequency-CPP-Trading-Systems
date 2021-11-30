#pragma once

#include "Band.h"

Band::Band() {
  meanPrice = 0;
  stdDeviation = 0;
  noOfElements = 0;
}

Band::~Band() {}

long Band::getMean() { return meanPrice; }

long Band::getStd() { return stdDeviation; }

void Band::insertNewData(long price, std::shared_ptr<OrderBook> book) {
  /*if (price > book->getLowestAsk()->getOrderPrice() + stdDeviation || price <
  book->getHighestBid()->getOrderPrice() - stdDeviation) { return;
      //this is just a measure to ensure data that is far from our bands is not
  affected
  }
   */
  long newMean = (meanPrice * noOfElements + price) / (noOfElements + 1);
  int newNoOfElements = noOfElements + 1;
  long newStdDeviation =
      ((price - newMean) * (price - newMean) / newNoOfElements) +
      (noOfElements / newNoOfElements) * (stdDeviation + meanPrice * meanPrice);
  meanPrice = newMean;
  stdDeviation = newStdDeviation;
  noOfElements = newNoOfElements;
}