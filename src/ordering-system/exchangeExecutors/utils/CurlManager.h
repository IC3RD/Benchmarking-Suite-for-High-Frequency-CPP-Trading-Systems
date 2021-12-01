#pragma once
#include <curl/curl.h>

#include <string>

class CurlManager {
 public:
  CurlManager();
  // Append a header of the form "key:value" to the request.
  void appendHeader(const std::string& header);
  void sendRequest(bool output);
  void initCurl();
  void addDestination(const std::string& destination);
  void addPostFields(const std::string& fields);
  void appendHeadersToRequest();

 private:
  CURL* curl;
  struct curl_slist* chunk;
};
