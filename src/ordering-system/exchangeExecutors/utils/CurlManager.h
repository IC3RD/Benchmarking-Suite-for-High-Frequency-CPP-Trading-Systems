#pragma once
#include <curl/curl.h>

#include <string>

class CurlManager {
 public:
  CurlManager();
  // Append a header of the form "key:value" to the curl chunk.
  void appendHeader(const std::string& header);
  // Add the curl chunk (which contains the headers) to the request.
  void appendHeadersToRequest();
  // Pass the request to curl to perform.
  void sendRequest(bool output);
  // Reset/Initialise internal curl object and chunk.
  void initCurl();
  // Add a URL to the request.
  void addDestination(const std::string& destination);
  // Add the post data to the request.
  void addPostFields(const std::string& fields);

 private:
  CURL* curl{};
  struct curl_slist* chunk{};
};
