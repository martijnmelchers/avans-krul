#include <memory>
#include <curl/curl.h>
#include "CurlWrapper.h"

curl_wrapper::~curl_wrapper()
{
	curl_easy_cleanup(curl);
}

CURL* curl_wrapper::get() const
{
	return curl;
}



