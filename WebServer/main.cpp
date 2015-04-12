#include "stdafx.h"

using namespace std;
using namespace web::http;
using namespace web::http::experimental::listener;

int main()
{
	auto config = make_shared<Configurator>();

	auto listener = make_shared<http_listener>(config->Uri());
	listener->support(methods::GET, ServiceHandler::Get);

	listener->open().then([&config](){
		wcout << config->Uri() << " server is open!!" << endl;
	}).wait();

	getchar();

	return 0;
}