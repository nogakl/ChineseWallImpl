
#include "../include/Subject.h"
#include "../include/ConflictInterest.h"
#include "../include/Dataset.h"

namespace ChineseWall {
	Dataset::Dataset(std::string name, ConflictInterest& conflictInterest) :
		m_name(name),
		m_conflictInterest(conflictInterest)
	{}
	Status Dataset::ReadAccess(Subject& subject)
	{
		if (m_conflictInterest.ReadAccess(subject) == Status::PermissionDenied) {
			m_accessList.AddPermission(subject.GetName(), Permission::Read);
			return Status::Success;
		}
		return m_accessList.GetPermission(subject.GetName(), Permission::Read);
	}

	Status Dataset::WriteAccess(Subject& subject)
	{
		return Status();
	}

	Status Dataset::AddPermission(Subject& subject, Permission permission)
	{
		return m_accessList.AddPermission(subject.GetName(), permission);
	}

	Status Dataset::RemovePermission(Subject& subject, Permission permission)
	{
		return m_accessList.RemovePermission(subject.GetName(), permission);
	}
}