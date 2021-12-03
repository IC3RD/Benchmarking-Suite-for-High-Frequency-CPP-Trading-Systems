#include "FileReaderListener.h"
using json = nlohmann::json;

FileReaderListener::FileReaderListener(OrderBook& orderBook,
                                       Exchange::ExchangeName exchange,
                                       std::string file)
    : OrderDataCollector(orderBook, exchange), fileToOpen(file) {}

FileReaderListener::~FileReaderListener() {}

void FileReaderListener::readDataFromFile() {
  std::string getLine;
  // parse string values and create a json object from them, pass that into
  // parseJson
  nlohmann::json example =
      json::object({{"ask", {{"price", 2}, {"volume", 1}}}});
  passJSON(example);
}

void FileReaderListener::passJSON(nlohmann::json json) {
  if (json.contains("ask")) {
    constructAndPassOrderData(OrderTypes::ASK, json.at("ask").at("price"),
                              json.at("ask").at("volume"));
  }
  if (json.contains("bid")) {
    constructAndPassOrderData(OrderTypes::BID, json.at("bid").at("price"),
                              json.at("bid").at("volume"));
  }
}