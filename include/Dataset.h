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
	private:
		std::string m_name;
		ConflictInterest &m_conflictInterest;
		AccessList m_accessList;
	};
}