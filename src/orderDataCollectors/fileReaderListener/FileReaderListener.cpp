#include "FileReaderListener.h"

#include <sstream>

FileReaderListener::FileReaderListener(OrderBook &orderBook,
                                       Exchange::ExchangeName exchange,
                                       std::string file)
    : OrderDataCollector(orderBook, exchange), fileToOpen(file) {}

FileReaderListener::~FileReaderListener() {}

void FileReaderListener::readDataFromFile() {
  file.open(fileToOpen);
  std::string line;
  getline(file, line);

  std::vector<std::string> tokens;
  std::istringstream iss(line);
  std::string item;
  while (std::getline(iss, item, ' ')) {
    tokens.push_back(
        item);  // this should always have 3 items (BID/ASK, price, volume)
  }

  int price = std::stoi(tokens[1]);
  double volume = std::stod(tokens[2]);
  if (tokens[0] == "BID") {
    constructAndPassOrderData(OrderTypes::BID, price, volume);
  } else {
    constructAndPassOrderData(OrderTypes::ASK, price, volume);
  }
}