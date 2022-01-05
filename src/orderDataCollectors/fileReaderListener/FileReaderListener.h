#pragma once

#include "orderDataCollectors/OrderDataCollector.h"

class FileReaderListener : OrderDataCollector {
 public:
  FileReaderListener(OrderBook&, Exchange::ExchangeName, std::string);
  ~FileReaderListener();
  void passJSON(nlohmann::json json);
  void readDataFromFile();

 private:
  const std::string fileToOpen;
};