#pragma once
#include "Common.h"

namespace ChineseWall {
	class ConflictInterest;
	class Subject;
	class Dataset {
	public:
		Dataset() = delete;
		Dataset(std::string name, std::shared_ptr<ConflictInterest> conflictInterest);
		Status ReadAccess(const Subject& subject);
		Status WriteAccess(const Subject& subject);
	private:
		std::string m_name;
		std::shared_ptr<ConflictInterest> m_conflictInterest;
		AccessList m_accessList;
	};
}