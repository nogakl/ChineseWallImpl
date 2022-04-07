
#include "../include/Dataset.h"
#include "../include/ConflictInterest.h"
namespace ChineseWall {
	Dataset::Dataset(std::string name, std::shared_ptr<ConflictInterest> conflictInterest) :
		m_name(name)
	{
		m_conflictInterest = std::move(conflictInterest);
	}
	Status Dataset::ReadAccess(const Subject& subject)
	{

		return m_accessList.GetAccess(subject, Permission::Read) == Status::Success || 
			m_conflictInterest->ReadAccess(subject) == Status::PermissionDenied ?
			Status::Success : 
			Status::PermissionDenied;
	}

	Status Dataset::WriteAccess(const Subject& subject)
	{
		return Status();
	}
}