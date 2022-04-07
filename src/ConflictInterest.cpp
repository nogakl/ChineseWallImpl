#include "..\include\ConflictInterest.h"
namespace ChineseWall {
    Status ChineseWall::ConflictInterest::ReadAccess(const Subject& subject)
    {
		return m_accessList.GetAccess(subject, Permission::Read);
    }

    Status ChineseWall::ConflictInterest::WriteAccess(const Subject& subject)
    {
        return Status();
    }
}