
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
std::ifstream ifs;
Json::Value root;
std::string basicName = "obj";
std::string objName = "";
std::string ownerName = "";
std::string readName = "";
std::string writeName = "";
std::string executeName = "";
std::string datasetName = "";
std::string ciName = "";
std::string objType = "";
int db = 0;
Subject* userSubject = nullptr;
std::string userSubjectName = "";

/*
* after opening the DB, this function parse the json file
* and add subject, object and permissions base on it.
* if there is an error returns 1, otherwise 0
*/
int buildTheSystem();

/*
* ============= Main Loop Handlers =============
*/

/*
*to read, enter the object to read from, the start position of the readand how many bytes to read
*/
void handleReadCommand();
/*
* to write, enter the object to write to, the start position of writing, string to writeand how many bytes to write
*/
void handleWriteCommand();
/*
* to add subject, enter subject name to create
*/
void handleAddSubjectCommand();
/*
* to add object, enter object name to create, its type(File or Thread) and its Dataset
*/
void handleAddObjectCommand();

int main()
{
	
	/* 
	* open data base at setup the system
	*/
	std::cout << "Plaese enter Database number (1-4)\n";
	std::cin >> db;

	ifs.open("example" + std::to_string(db) + ".json");
	if (ifs.is_open() == false) {
		std::cout << "Failed to Open\n";
	}

	std::cout << "Building the system ....... \n";
	if (buildTheSystem() != 0) return EXIT_FAILURE;
	/*
	* Main Loop : 
	* 1. if the user want to exit : enter 1
	* 2. the user login with subject name
	* 3. the user enter the required command : Read | Write | Add subject | Add object
	* 4. the user enter the relevant data for the command :
	*	- to read, enter the object to read from, the start position of the read and how many bytes to read
	*	- to write, enter the object to write to, the start position of writing, string to write and how many bytes to write
	*	- to add subject, enter subject name to create
	*	- to add object, enter object name to create, its type (File or Thread) and its Dataset
	*/
	int toExit = 2;
	while (toExit != 0) {
		userSubjectName = "";
		if (toExit == 2) {
			userSubject = nullptr;
			/* gets the user name from cmd */
			std::cout << "Please enter your subject name\n";
			std::cin >> userSubjectName;

			/* try to login to user name */
			userSubject = Manager::Instance().GetSubject(userSubjectName);
		}
		if (userSubject != nullptr)
		{
			std::cout << "Please enter commad:\n1 - Read\n2 - Write\n3 - Add Subject\n4 - Add Object\n";
			int cmd = 0;
			std::cin >> cmd;
			switch (cmd)
			{
			case 1:
				handleReadCommand();
				break;
			case 2:
				handleWriteCommand();
				break;
			case 3:
				handleAddSubjectCommand();
				break;
			case 4:
				handleAddObjectCommand();
				break;
			default:
				std::cout << "OOPS! wrong command :\\";
			}
		}

		std::cout << "to exit enter 0\nto continue with same username enter 1\nto continue with new username enter 2\n";
		std::cin >> toExit;
	}
}

int buildTheSystem() {
	Json::CharReaderBuilder builder;
	builder["collectComments"] = true;
	JSONCPP_STRING errs;
	if (!parseFromStream(builder, ifs, &root, &errs)) {
		std::cout << errs << std::endl;
		return EXIT_FAILURE;
	}

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
	return 0;
}

void handleReadCommand() {
	std::string userObjectName;
	Object* userObject;
	uint8_t bufferData[THREAD_MEMORY_SPACE] = { 0 };
	int position = 0, numOfBytes = 0;
	std::cout << "Please enter object name\n";
	std::cin >> userObjectName;

	userObject = Manager::Instance().GetObject(userObjectName);
	if (userObject != nullptr)
	{
		std::cout << "Please enter position\n";
		std::cin >> position;
		std::cout << "Please enter num of bytes to read\n";
		std::cin >> numOfBytes;
		std::cout << "Access " << (userObject->Read(*userSubject, position, bufferData, numOfBytes) == Status::Success ? "Success" : "Denied") << std::endl;
		std::cout << "Read from object : " << bufferData << std::endl;
	}
	else std::cout << "Wrong object name!\n";
}
void handleWriteCommand() {
	std::string userObjectName, dataset, objectType;
	Object* userObject;
	uint8_t bufferData[THREAD_MEMORY_SPACE] = { 0 };
	int position = 0, numOfBytes = 0;
	userSubject = Manager::Instance().GetSubject(userSubjectName);

	std::cout << "Please enter object name\n";
	std::cin >> userObjectName;

	userObject = Manager::Instance().GetObject(userObjectName);
	if (userObject != nullptr)
	{
		std::cout << "Please enter position\n";
		std::cin >> position;
		std::cout << "Please enter num of bytes to write\n";
		std::cin >> numOfBytes;
		std::cout << "Please enter string to write\n";
		std::cin >> bufferData;
		std::cout << "Access " << (userObject->Write(*userSubject, position, bufferData, numOfBytes) == Status::Success ? "Success" : "Denied") << std::endl;
	}
	else std::cout << "Wrong object name!\n";
}
void handleAddSubjectCommand() {
	std::string userObjectName;
	std::cout << "Please enter subject name\n";
	std::cin >> userObjectName;
	std::cout << ((Manager::Instance().AddSubject(userObjectName) == Status::Success) ? "Success" : "Failed") << "to add subject\n";
}
void handleAddObjectCommand() {
	std::string userObjectName, dataset, objectType;
	std::cout << "Please enter object name\n";
	std::cin >> userObjectName;
	std::cout << "Please enter object type : File or Thread\n";
	std::cin >> objectType;
	std::cout << "Please enter dataset name\n";
	std::cin >> dataset;
	std::cout << ((Manager::Instance().AddObject(userObjectName, objectType, dataset, userSubjectName) == Status::Success) ? "Success" : "Failed") << "to add object\n";
}