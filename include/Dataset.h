#pragma once
#include "Common.h"

namespace ChineseWall {
	class ConflictInterest;
	class Subject;
	class Dataset {
	public:
		Dataset() = delete;
		Dataset(std::string name, ConflictInterest &conflictInterest);
		Status ReadAccess(Subject& subject);
		Status WriteAccess(Subject& subject);
		Status AddPermission(Subject& subject, Permission permission);
		Status RemovePermission(Subject& subject, Permission permission);
	private:
		std::string m_name;
		ConflictInterest &m_conflictInterest;
		AccessList m_accessList;
	};
}