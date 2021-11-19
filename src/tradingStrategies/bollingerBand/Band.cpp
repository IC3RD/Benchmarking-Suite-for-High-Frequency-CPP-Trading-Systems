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

void Band::insertNewData(long price) {
  long newMean = (meanPrice * noOfElements + price) / (noOfElements + 1);
  int newNoOfElements = noOfElements + 1;
  long newStdDeviation =
      ((price - newMean) * (price - newMean) / newNoOfElements) +
      (noOfElements / newNoOfElements) * (stdDeviation + meanPrice * meanPrice);
  meanPrice = newMean;
  stdDeviation = newStdDeviation;
  noOfElements = newNoOfElements;
}