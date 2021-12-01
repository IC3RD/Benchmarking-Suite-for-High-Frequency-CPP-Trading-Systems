#pragma once
#include <curl/curl.h>

#include <string>

class curlManager {
 public:
  curlManager();
  // Append a header of the form "key:value" to the request.
  void addHeader(const std::string& header);
  void sendRequest(bool output);
  void initCurl();
  void addDestination(const std::string& destination);
  void addPostFields(const std::string& fields);

 private:
  CURL* curl{};
  struct curl_slist* chunk{};
};
