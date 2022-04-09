#include "../include/Subject.h"
#include "..\include\ConflictInterest.h"
#include "../include/Dataset.h"
#include "../include/Object.h"
#include "..\include\Manager.h"

namespace ChineseWall {
    ConflictInterest::ConflictInterest(std::string name) : 
        m_name(name) { }

    Status ChineseWall::ConflictInterest::ReadAccess(Subject& subject)
    {
		return m_accessList.GetPermission(subject.GetName(), Permission::Read);
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
        return Manager::Instance().IsPermissionExclusive(subject, Permission::Write, m_name);
    }
    std::string ConflictInterest::GetName()
    {
        return m_name;
    }
}