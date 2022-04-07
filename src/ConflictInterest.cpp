#include "../include/Subject.h"
#include "..\include\ConflictInterest.h"

namespace ChineseWall {
    ConflictInterest::ConflictInterest(std::string name) : 
        m_name(name) { }

    Status ChineseWall::ConflictInterest::ReadAccess(Subject& subject)
    {
		return m_accessList.GetAccess(subject.GetName(), Permission::Read);
    }

    Status ChineseWall::ConflictInterest::WriteAccess(Subject& subject)
    {
        return Status();
    }
}