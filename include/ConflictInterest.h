#pragma once
#include <memory>
#include <map>
#include <list>
#include <string>
#include "Status.h"
#include "Permissions.h"

namespace ChineseWall {
	class Subject;
	class ConflictInterest {
	public:
		Status ReadAccess(const Subject& subject);
		Status WriteAccess(const Subject& subject);
	private:
		std::string m_name;
		std::map<Subject, std::unique_ptr<std::list<Permission>>> m_accessList;
	};
}