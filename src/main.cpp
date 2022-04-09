
#include <iostream>
#include "../jsoncpp/include/json/json.h"
#include <fstream>
#include <string>

int main()
{
	std::fstream file("db.json");
	Json::Value actualJson;
	Json::Reader reader;
}
