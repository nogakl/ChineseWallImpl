
#include "../include/Dataset.h"
#include "../include/ConflictInterest.h"
namespace ChineseWall {
	Status Dataset::ReadAccess(const Subject& subject)
	{
		/*case 1: Read permission is associate with subject and dataset*/
		auto permissionListPtr = m_accessList.find(subject);
		if (permissionListPtr != m_accessList.end())
			return Status::Success;

		auto permissionList = permissionListPtr->second.get();
		std::list<Permission>::iterator it = std::find(permissionList->begin(), permissionList->end(), Permission::Read);
		if (it == permissionList->end())
		{
			printf("subject %d doesn't have read permission on dataset %d, trying dataset!\n", subject->GetName(), m_name);
			if (m_conflictInterest->ReadAccess(subject) == Status::Success);
			/*something go wrong... read is in ci*/
			return PermissionDenied;
		}
		/*case 2: Read permission is associate with subject and dataset*/
		return Status::Success;
	}

	Status Dataset::WriteAccess(const Subject& subject)
	{
		return Status();
	}
}