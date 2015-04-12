#include "stdafx.h"

using namespace std;
using namespace web;

using utility::string_t;
using web::http::http_request;


shared_ptr<vector<string_t>> ServiceHandler::Uri(http_request req)
{
	auto result = make_shared<vector<string_t>>();
	auto path = req.request_uri().path();

	string_t token;
	for (auto ch : path)
	{
		if (ch == U("/")[0])
		{
			if (!token.empty())
			{
				result->push_back(token);
				token.clear();
			}
		}
		else
			token += ch;
	}
	if (!token.empty())	result->push_back(token);

	return result;
}

void ServiceHandler::Get(http_request req)
{
	json::value ret;
	ret[U("uri")] = json::value::array();

	auto uriList = Uri(req);
	for (int i = 0; i < uriList->size(); i++)
		ret[U("uri")][i] = json::value::string((*uriList)[i]);
	
	ret[U("value")] = json::value::string(U("hello,world!!"));
	req.reply(http::status_codes::OK, ret);	
}

void ServiceHandler::Post(http_request req)
{
	if(req.headers().content_type() != U("application/json"))
	{
		json::value ret;
		ret[U("err-msg")] = json::value::string(U("content-type is not application/json"));
		req.extract_string().then([&](pplx::task<utility::string_t> task){
			ret[U("req")] = json::value::string(task.get());
			req.reply(http::status_codes::OK, ret);
		}).wait();
		return;
	}
	
	json::value ret;
	req.extract_json().then([&](pplx::task<json::value> task){
		ret = task.get();
	}).wait();
	req.reply(http::status_codes::OK, ret);
}