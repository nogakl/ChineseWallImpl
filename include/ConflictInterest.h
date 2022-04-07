#pragma once
#include "Common.h"

namespace ChineseWall {
	class Subject;
	class ConflictInterest {
	public:
		Status ReadAccess(const Subject& subject);
		Status WriteAccess(const Subject& subject);
	private:
		std::string m_name;
		AccessList m_accessList;
	};
}