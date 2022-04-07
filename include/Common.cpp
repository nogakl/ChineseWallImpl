#include "Common.h"
namespace ChineseWall {
	Status AccessList::GetAccess(const Subject& subject, Permission permission)
	{
		/* varify that subject is in access list */
		auto permissionListPtr = m_accessList.find(subject);
		if (permissionListPtr == m_accessList.end())
			return Status::PermissionDenied;

		/* varify that subject has the relevant permission */
		auto permissionList = permissionListPtr->second.get();
		std::list<Permission>::iterator it = std::find(permissionList->begin(), permissionList->end(), permission);
		if (it == permissionList->end())
			return Status::PermissionDenied;

		return Status::Success;
	}
	Status AccessList::AddPermission(const Subject& subject, Permission permission)
	{
		/* if subject is not in access list- we should create new permission list */
		auto permissionListPtr = m_accessList.find(subject);
		if (permissionListPtr == m_accessList.end()) {
			std::shared_ptr<std::list<Permission>> list = std::make_unique<std::list<Permission>>();
			list->push_back(permission);
			m_accessList.at(subject) = std::move(list);
		}

		/* otherwise, we should insert the permission to its list, if not exists */
		auto permissionList = permissionListPtr->second.get();
		std::list<Permission>::iterator it = std::find(permissionList->begin(), permissionList->end(), permission);
		if (it == permissionList->end())
			permissionList->push_back(permission);

		return Status::Success;
	}

	Status AccessList::RemovePermission(const Subject& subject, Permission permission)
	{
		auto permissionListPtr = m_accessList.find(subject);
		if (permissionListPtr == m_accessList.end()) {
			printf("subject is not in access list, failed to remove permission\n");
			return Status::Failure;
		}

		auto permissionList = permissionListPtr->second.get();
		std::list<Permission>::iterator it = std::find(permissionList->begin(), permissionList->end(), permission);
		if (it == permissionList->end()) {
			printf("subject doesn't has the specific permission, failed to remove permission\n");
			return Status::Failure;
		}
		permissionList->remove(permission);
		return Status::Success;
	}
	Status AccessList::RemoveSubject(const Subject& subject)
	{
		auto permissionListPtr = m_accessList.find(subject);
		if (permissionListPtr == m_accessList.end()) {
			printf("subject is not in access list, failed to remove subject\n");
			return Status::Failure;
		}
		m_accessList.erase(subject);
		return Status::Success;
	}
}