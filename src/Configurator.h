#pragma once

#include "stdafx.h"

class Configurator
{
private:
	web::json::value _value;
public:
	Configurator()
	{
		std::ifstream f("configure.json");
		_value = web::json::value::parse(f);
		f.close();
	}

	utility::string_t Uri()	{ return _value[U("uri")].as_string(); }
};