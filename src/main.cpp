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
#ifdef _UTF16_STRINGS
		wcout << config->Uri() << " server is open!!" << endl;
#else
		cout << config->Uri() << " server is open!!" << endl;
#endif
	}).wait();

	getchar();

	return 0;
}