#pragma once
#include "Common.h"

namespace ChineseWall {
	class Subject;
	class ConflictInterest {
	public:
		explicit ConflictInterest(std::string name);
		Status ReadAccess(Subject& subject);
		Status AddPermission(Subject& subject, Permission permission);
		Status RemovePermission(Subject& subject, Permission permission);
		Status WriteAccess(Subject& subject);
	private:
		std::string m_name;
		AccessList m_accessList;
	};
}