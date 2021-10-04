#pragma once
#include <memory>
#include <curl/curl.h>

class curl_wrapper
{
	CURL* curl;

public:
	curl_wrapper(CURL* curl) : curl(curl) {};

	~curl_wrapper();
	CURL* get() const;
};
