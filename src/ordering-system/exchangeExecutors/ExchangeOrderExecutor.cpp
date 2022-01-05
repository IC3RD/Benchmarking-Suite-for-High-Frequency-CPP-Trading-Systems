#include "ExchangeOrderExecutor.h"

ExchangeOrderExecutor::ExchangeOrderExecutor() {
  this->curlManager = std::make_unique<CurlManager>();
}

/* Function that sends prepared curl object over HTTP. */
void ExchangeOrderExecutor::sendOrder() { curlManager->sendRequest(output); }

void ExchangeOrderExecutor::enableOutput() { this->output = true; }
void ExchangeOrderExecutor::disableOutput() { this->output = false; }
