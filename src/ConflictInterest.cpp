#include "..\include\ConflictInterest.h"
namespace ChineseWall {
    Status ChineseWall::ConflictInterest::ReadAccess(const Subject& subject)
    {
		auto permissionListPtr = m_accessList.find(subject);
		if (permissionListPtr == m_accessList.end())
			return Status::PermissionDenied;

		auto permissionList = permissionListPtr->second.get();
		std::list<Permission>::iterator it = std::find(permissionList->begin(), permissionList->end(), Permission::Read);
		if (it == permissionList->end())
			return Status::PermissionDenied;
		
		printf("oh, read access is associate with subject %s and ci %s\n", subject.GetName(), m_name);
		return Status::Success;
    }

    Status ChineseWall::ConflictInterest::WriteAccess(const Subject& subject)
    {
        return Status();
    }
}