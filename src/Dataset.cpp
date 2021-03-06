#include "Subject.h"
#include "ConflictInterest.h"
#include "Dataset.h"

namespace ChineseWall {
	Dataset::Dataset(std::string name, ConflictInterest& conflictInterest) :
		m_name(name),
		m_conflictInterest(conflictInterest)
	{}
	Status Dataset::ReadAccess(Subject& subject)
	{
		return m_accessList.GetPermission(subject.GetName(), Permission::Read) != Status::Success ?
			(m_conflictInterest.ReadAccess(subject) == Status::PermissionDenied) ? AddPermission(subject, Permission::Read) : Status::PermissionDenied :
			Status::Success;
	}

	Status Dataset::WriteAccess(Subject& subject)
	{
		return m_accessList.GetPermission(subject.GetName(), Permission::Write) != Status::Success ?
			(m_conflictInterest.WriteAccess(subject) == Status::Success) ? AddPermission(subject, Permission::Write) : Status::PermissionDenied :
			Status::Success;
	}

	Status Dataset::AddPermission(Subject& subject, Permission permission)
	{
		return m_conflictInterest.AddPermission(subject, permission) == Status::Success ?
			m_accessList.AddPermission(subject.GetName(), permission) : 
			Status::Failure;
	}

	Status Dataset::RemovePermission(Subject& subject, Permission permission)
	{
		return m_accessList.RemovePermission(subject.GetName(), permission);
	}
}