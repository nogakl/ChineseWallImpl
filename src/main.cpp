
#include <iostream>
#include "../jsoncpp/include/json/json.h"
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include "../jsoncpp/include/json/value.h"
#include "../include/Subject.h"
#include "../include/Dataset.h"
#include "../include/ConflictInterest.h"
#include "../include/Object.h"
#include "../include/Manager.h"

using namespace ChineseWall;

int main()
{
	Json::Value root;
	std::ifstream ifs;
	int db = 0;

	std::cout << "Plaese enter Database number (1-2)\n";
	std::cin >> db;

	ifs.open("example" + std::to_string(db) + ".json");
	
	std::cout << "Building the system ....... \n";

	Json::CharReaderBuilder builder;
	builder["collectComments"] = true;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, ifs, &root, &errs)) {
		std::cout << errs << std::endl;
		return EXIT_FAILURE;
	}

	std::string basicName = "obj";
	std::string objName = "";
	std::string ownerName = "";
	std::string readName = "";
	std::string writeName = "";
	std::string executeName = "";
	std::string datasetName = "";
	std::string ciName = "";

	int i = 1;
	std::string fullName = basicName + std::to_string(i);
	while(root[fullName]["name"].isNull() != true) {
		objName = root[fullName]["name"].asString();
		datasetName = root[fullName]["dataset"].asString();
		ciName = root[fullName]["conflictInterest"].asString();
		ownerName = root[fullName]["owner"].asString();

		Manager::Instance().AddSubject(ownerName);
		Manager::Instance().AddConflictInterest(ciName);
		Manager::Instance().AddDataset(datasetName, ciName);
		Manager::Instance().AddObject(objName, datasetName, ownerName);

		auto obj = Manager::Instance().GetObject(objName);

		int j = 0;
		while (root[fullName]["read"][j].isNull() != true) {
			readName = root[fullName]["read"][j].asString();
			Manager::Instance().AddSubject(readName);
			auto readSub = Manager::Instance().GetSubject(readName);
			obj->AddPermission(*readSub, Permission::Read);
			++j;
		}
		j = 0;
		while (root[fullName]["write"][j].isNull() != true) {
			writeName = root[fullName]["write"][j].asString();
			Manager::Instance().AddSubject(writeName);
			auto writeSub = Manager::Instance().GetSubject(writeName);
			obj->AddPermission(*writeSub, Permission::Write);
			++j;
		}
		j = 0;
		while (root[fullName]["execute"][j].isNull() != true) {
			executeName = root[fullName]["execute"][j].asString();
			Manager::Instance().AddSubject(executeName);
			auto executeSub = Manager::Instance().GetSubject(executeName);
			obj->AddPermission(*executeSub, Permission::Execute);
			++j;
		}
		++i;
		fullName = basicName + std::to_string(i);
	}

	std::cout << "Finished to build the system!\n";
	int toExit = 0;
	while (toExit == 0) {
		std::string userSubjectName = "";
		std::cout << "Please enter your subject name\n";
		std::cin >> userSubjectName;
		auto userSubject = Manager::Instance().GetSubject(userSubjectName);
		if (userSubject == nullptr)
		{
			std::cout << "Wrong subject name!\nTo try again enter 0, to exit 1\n";
			std::cin >> toExit;
			break;
		}
		else {
			std::string cmd; std::string userObjectName;
			std::cout << "Enter command\n";
			std::cin >> cmd;
			std::cout << "Enter object name\n";
			std::cin >> userObjectName;
			auto userObject = Manager::Instance().GetObject(userObjectName);
			if (userObject == nullptr)
			{
				std::cout << "Wrong object name!\nTo try again enter 0, to exit 1\n";
				std::cin >> toExit;
			}
			else {
				if (cmd.compare("read") == 0) {
					std::cout << "Got read!\n";
					std::cout << "Access " << (userObject->Read(*userSubject) == Status::Success ? "Success" : "Denied") << std::endl;
				}
				else if (cmd.compare("write") == 0) {
					std::cout << "Got wrtie!\n";
					std::cout << "Access " << (userObject->Write(*userSubject) == Status::Success ? "Success" : "Denied") << std::endl;
				}
			}
		}
		std::cout << "to exit enter 1, to contain 0\n";
		std::cin >> toExit;
	}
}	

