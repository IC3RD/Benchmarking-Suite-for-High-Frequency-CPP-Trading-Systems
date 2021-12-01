#include "CurlManager.h"

#include <curl/curl.h>

#include <iostream>
#include <string>

CurlManager::CurlManager() { initCurl(); }

/* Callback function to disable curl outputs.*/
size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp) {
  return size * nmemb;
}

void CurlManager::initCurl() {
#ifndef ENABLE_CPP_BENCHMARKS
  this->curl = curl_easy_init();
  this->chunk = nullptr;
#endif
}

void CurlManager::appendHeader(const std::string& header) {
#ifndef ENABLE_CPP_BENCHMARKS
  this->chunk = curl_slist_append(chunk, header.c_str());
#endif
}

void CurlManager::appendHeadersToRequest() {
#ifndef ENABLE_CPP_BENCHMARKS
  curl_easy_setopt(this->curl, CURLOPT_HTTPHEADER, this->chunk);
#endif
}

void CurlManager::sendRequest(bool output) {
#ifndef ENABLE_CPP_BENCHMARKS
  if (!output) {
    curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, write_data);
  }
  if (curl) {
    auto res = curl_easy_perform(this->curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
    if (output) {
      std::cout << "\n";
    }
  }
#endif
}
void CurlManager::addDestination(const std::string& destination) {
#ifndef ENABLE_CPP_BENCHMARKS
  curl_easy_setopt(this->curl, CURLOPT_URL, destination.c_str());
#endif
}
void CurlManager::addPostFields(const std::string& fields) {
#ifndef ENABLE_CPP_BENCHMARKS
  curl_easy_setopt(this->curl, CURLOPT_POST, 1L);
  curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, fields.c_str());
  curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, fields.length());
#endif
}
