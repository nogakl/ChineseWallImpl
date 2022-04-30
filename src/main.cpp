
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
#include "../include/File.h"
#include "../include/Thread.h"

using namespace ChineseWall;

int main()
{
	Json::Value root;
	std::ifstream ifs;
	int db = 0;

	std::cout << "Plaese enter Database number (1-2)\n";
	std::cin >> db;

	ifs.open("example" + std::to_string(db) + ".json");
	if (ifs.is_open() == false) {
		std::cout << "Failed to Open\n";
	}

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
	std::string objType = "";

	int i = 1;
	std::string fullName = basicName + std::to_string(i);
	while (root[fullName]["name"].isNull() != true) {
		objName = root[fullName]["name"].asString();
		objType = root[fullName]["type"].asString();
		datasetName = root[fullName]["dataset"].asString();
		ciName = root[fullName]["conflictInterest"].asString();
		ownerName = root[fullName]["owner"].asString();

		Manager::Instance().AddSubject(ownerName);
		Manager::Instance().AddConflictInterest(ciName);
		Manager::Instance().AddDataset(datasetName, ciName);
		Manager::Instance().AddObject(objName, objType, datasetName, ownerName);

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
		std::string userObjectName, dataset, objectType;
		Object* userObject;
		uint8_t bufferData[THREAD_MEMORY_SPACE] = { 0 };
		int position = 0, numOfBytes = 0;
		if (userSubject == nullptr)
		{
			std::cout << "Wrong subject name!\nTo try again enter 0, to exit 1\n";
			std::cin >> toExit;
			break;
		}
		else {
			std::cout << "Please enter commad:\n1 - Read\n2 - Write\n3 - Add Subject\n4 - Add Object\n";
			int cmd = 0;
			std::cin >> cmd;
			switch (cmd)
			{
			case 1:
				std::cout << "Please enter object name\n";
				std::cin >> userObjectName;

				userObject = Manager::Instance().GetObject(userObjectName);
				if (userObject == nullptr)
				{
					std::cout << "Wrong object name!\nTo try again enter 0, to exit 1\n";
					std::cin >> toExit;
				}
				else {
					std::cout << "Please enter position\n";
					std::cin >> position;
					std::cout << "Please enter num of bytes to read\n";
					std::cin >> numOfBytes;
					std::cout << "Access " << (userObject->Read(*userSubject, position, bufferData, numOfBytes) == Status::Success ? "Success" : "Denied") << std::endl;
					std::cout << "Read from object : " << bufferData << std::endl;
				}
				break;
			case 2:
				std::cout << "Please enter object name\n";
				std::cin >> userObjectName;

				userObject = Manager::Instance().GetObject(userObjectName);
				if (userObject == nullptr)
				{
					std::cout << "Wrong object name!\nTo try again enter 0, to exit 1\n";
					std::cin >> toExit;
				}
				std::cout << "Please enter position\n";
				std::cin >> position;
				std::cout << "Please enter num of bytes to write\n";
				std::cin >> numOfBytes;
				std::cout << "Please enter string to write\n";
				std::cin >> bufferData;
				std::cout << "Access " << (userObject->Write(*userSubject, position, bufferData, numOfBytes) == Status::Success ? "Success" : "Denied") << std::endl;
				break;
			case 3:
				std::cout << "Please enter subject name\n";
				std::cin >> userObjectName;
				std::cout << ((Manager::Instance().AddSubject(userObjectName) == Status::Success) ? "Success" : "Failed") << "to add subject\n";
				break;
			case 4:
				std::cout << "Please enter object name\n";
				std::cin >> userObjectName;
				std::cout << "Please enter object type : File or Thread\n";
				std::cin >> objectType;
				std::cout << "Please enter dataset name\n";
				std::cin >> dataset;
				std::cout << ((Manager::Instance().AddObject(userObjectName, objectType, dataset, userSubjectName) == Status::Success) ? "Success" : "Failed") << "to add object\n";
				break;
			default:
				std::cout << "OOPS! wrong command :\\";
			}
		}

		std::cout << "to exit enter 1, to contain 0\n";
		std::cin >> toExit;
	}
}

