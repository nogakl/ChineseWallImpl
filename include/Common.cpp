#include "Subject.h"
#include "Common.h"
namespace ChineseWall {
	Status AccessList::GetAccess(std::string subject, Permission permission)
	{
		/* varify that subject is in access list */
		auto permissionListPtr = m_accessList.find(subject);
		if (permissionListPtr == m_accessList.end())
			return Status::PermissionDenied;

		/* varify that subject has the relevant permission */
		auto permissionList = permissionListPtr->second;
		std::list<Permission>::iterator it = std::find(permissionList.begin(), permissionList.end(), permission);
		if (it == permissionList.end())
			return Status::PermissionDenied;

		return Status::Success;
	}
	Status AccessList::AddPermission(std::string subject, Permission permission)
	{
		/* if subject is not in access list- we should create new permission list */
		auto permissionListPtr = m_accessList.find(subject);
		if (permissionListPtr == m_accessList.end()) {
			std::list<Permission> l;
			l.push_back(permission);
			m_accessList.insert(std::pair<std::string, std::list<Permission>>(subject, l));
		}
		else {
			/* otherwise, we should insert the permission to its list, if not exists */
			auto permissionList = permissionListPtr->second;
			std::list<Permission>::iterator it = std::find(permissionList.begin(), permissionList.end(), permission);
			if (it == permissionList.end()) {
				permissionList.push_back(permission);
				m_accessList.at(subject) = permissionList;
			}
		}
		return Status::Success;
	}

	Status AccessList::RemovePermission(std::string subject, Permission permission)
	{
		auto permissionListPtr = m_accessList.find(subject);
		if (permissionListPtr == m_accessList.end()) {
			printf("subject is not in access list, failed to remove permission\n");
			return Status::Failure;
		}

		auto permissionList = permissionListPtr->second;
		std::list<Permission>::iterator it = std::find(permissionList.begin(), permissionList.end(), permission);
		if (it == permissionList.end()) {
			printf("subject doesn't has the specific permission, failed to remove permission\n");
			return Status::Failure;
		}
		permissionList.remove(permission);
		m_accessList.at(subject) = permissionList;
		return Status::Success;
	}
	Status AccessList::RemoveSubject(std::string subject)
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