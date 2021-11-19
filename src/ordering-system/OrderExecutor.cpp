#include "OrderExecutor.h"

// We should keep this file in the event we need to implement some behaviour
// that is common to the subclasses.

// A function that could disable message sending depending on benchmark.
void OrderExecutor::sendOrder(CURL *curl) {
  if(!benchmark) {
    auto res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }

    /* always cleanup */
    curl_easy_cleanup(curl);
    std::cout << "\n";
  }
}

void OrderExecutor::enableBenchmarking() {
  this->benchmark = true;
}

void OrderExecutor::disableBenchmarking() {
  this->benchmark = false;
}
