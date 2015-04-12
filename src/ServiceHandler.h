#pragma once

#include "stdafx.h"

using namespace std;
using web::http::http_request;

class ServiceHandler
{
private:
public:
	static shared_ptr<vector<utility::string_t>> Uri(http_request req);
	static void Get(http_request req);
	static void Post(http_request req);
};