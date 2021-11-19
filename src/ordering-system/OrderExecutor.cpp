#include "OrderExecutor.h"

// We should keep this file in the event we need to implement some behaviour
// that is common to the subclasses.

// dummy function to prevent printing.
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
  return size * nmemb;
}

// A function that could disable message sending depending on benchmark.
void OrderExecutor::sendOrder(CURL *curl) {
  if(!output) {
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  }

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

void OrderExecutor::enableOutput() {
  this->output = true;
}

void OrderExecutor::disableOutput() {
  this->output = false;

}

void OrderExecutor::enableBenchmarking() {
  this->benchmark = true;
}

void OrderExecutor::disableBenchmarking() {
  this->benchmark = false;
}
