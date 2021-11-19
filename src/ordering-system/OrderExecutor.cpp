#include "OrderExecutor.h"

#include <utility>

/* Function required as argument to CURLOPT_WRITEFUNCTION.
 * Is currently defined to disable outputs. */
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
  return size * nmemb;
}

/* Function that sends prepared curl object over HTTP. */
void OrderExecutor::sendOrder(CURL *curl) {
  if (!output) {
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  }

  if (!benchmark) {
    auto res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);
    if (output) {
      std::cout << "\n";
    }
  }
}

void OrderExecutor::enableOutput() { this->output = true; }
void OrderExecutor::disableOutput() { this->output = false; }
void OrderExecutor::enableBenchmarking() { this->benchmark = true; }
void OrderExecutor::disableBenchmarking() { this->benchmark = false; }
OrderExecutor::OrderExecutor(std::string secret_key, std::string public_key) {
  this->secret_key = std::move(secret_key);
  this->public_key = std::move(public_key);
}
void OrderExecutor::printOrderDetails(const std::string &order_data) {
  if (output) {
    std::cout << "Submitting order with data: " + order_data + " to " +
                     getExchangeName() + "..."
              << std::endl;
  }
}
