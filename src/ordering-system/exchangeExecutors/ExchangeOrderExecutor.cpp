#include "ExchangeOrderExecutor.h"

/* Function required as argument to CURLOPT_WRITEFUNCTION.
 * Is currently defined to disable outputs. */
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
  return size * nmemb;
}

/* Function that sends prepared curl object over HTTP. */
void ExchangeOrderExecutor::sendOrder(CURL *curl) {
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

void ExchangeOrderExecutor::enableOutput() { this->output = true; }
void ExchangeOrderExecutor::disableOutput() { this->output = false; }
void ExchangeOrderExecutor::enableBenchmarking() { this->benchmark = true; }
void ExchangeOrderExecutor::disableBenchmarking() { this->benchmark = false; }
