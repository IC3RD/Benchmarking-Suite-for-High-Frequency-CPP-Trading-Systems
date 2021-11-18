#pragma once

#include "orderDataCollectors/OrderDataCollector.h"

class FileReaderListener : OrderDataCollector {
 public:
  FileReaderListener(OrderBook&, Exchange::ExchangeName, std::string);
  ~FileReaderListener();

 private:
  const std::string fileToOpen;
  void readDataFromFile();
};