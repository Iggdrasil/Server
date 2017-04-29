#pragma once
#include<vector>
#include "HttpHeader.h"

struct HttpRequest
{
	std::string method;
	std::string uri;
	int http_version_major;
	int http_version_minor;
	std::vector<HttpHeader> headers;

	size_t header_len;
};

