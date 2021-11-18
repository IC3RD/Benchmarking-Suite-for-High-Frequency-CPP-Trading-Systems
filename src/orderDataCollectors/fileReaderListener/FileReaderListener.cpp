#include "FileReaderListener.h"

FileReaderListener::FileReaderListener(OrderBook& orderBook,
                                       Exchange::ExchangeName exchange,
                                       std::string file)
    : OrderDataListener(orderBook, exchange), fileToOpen(file) {}

FileReaderListener::~FileReaderListener() {}

void FileReaderListener::readDataFromFile() {
  std::string getLine;
  // constructAndPassOrderData(// parsed string)
}