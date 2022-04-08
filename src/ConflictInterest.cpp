#include "../include/Subject.h"
#include "..\include\ConflictInterest.h"

namespace ChineseWall {
    ConflictInterest::ConflictInterest(std::string name) : 
        m_name(name) { }

    Status ChineseWall::ConflictInterest::ReadAccess(Subject& subject)
    {
		return m_accessList.GetAccess(subject.GetName(), Permission::Read);
    }

    Status ConflictInterest::AddPermission(Subject& subject, Permission permission)
    {
        return m_accessList.AddPermission(subject.GetName(), permission);
    }

    Status ConflictInterest::RemovePermission(Subject& subject, Permission permission)
    {
        return m_accessList.RemovePermission(subject.GetName(), permission);
    }

    Status ChineseWall::ConflictInterest::WriteAccess(Subject& subject)
    {
        return Status();
    }
}