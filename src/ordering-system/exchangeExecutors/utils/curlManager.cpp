#include "curlManager.h"

#include <curl/curl.h>

#include <iostream>
#include <string>

curlManager::curlManager() { initCurl(); }

void curlManager::initCurl() {
  this->curl = curl_easy_init();
  this->chunk = nullptr;
}

void curlManager::addHeader(const std::string& header) {
  this->chunk = curl_slist_append(chunk, header.c_str());
}

void curlManager::sendRequest(bool output) {
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
void curlManager::addDestination(const std::string& destination) {
  curl_easy_setopt(this->curl, CURLOPT_URL, destination.c_str());
}
void curlManager::addPostFields(const std::string& fields) {
  curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, fields.c_str());
  curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, fields.length());
}
