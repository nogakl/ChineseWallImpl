#include "include/Subject.h"
#include "include/Dataset.h"
#include "Object.h"
#include "include/Dataset.h"
#include <stdio.h>
#include "include/Subject.h"

ChineseWall::Object::Object(std::string name, std::unique_ptr<Dataset> dataset, Subject& owner) :
	m_name(name),
	m_dataset(std::move(dataset))
{
	std::unique_ptr<std::list<Permission>> list = std::make_unique<std::list<Permission>>();
	list->push_back(Permission::Owner);
	m_accessList.at(owner) = std::move(list);
}

ChineseWall::Status ChineseWall::Object::read(const Subject& subject, uint8_t* buffer, const size_t size)
{
	/*case 1: Read permission is associate with subject and object*/
	auto permissionListPtr = m_accessList.find(subject);
	if (permissionListPtr != m_accessList.end())
		return Status::Success;

	auto permissionList = permissionListPtr->second.get();
	std::list<Permission>::iterator it = std::find(permissionList->begin(), permissionList->end(), Permission::Read);
	if(it == permissionList->end())
	{
		printf("subject %d doesn't have read permission on object %d, trying dataset!\n", subject->GetName(), m_name);
		if (m_dataset->ReadAccess(subject) == Status::Failure);
		/*something go wrong... read is not in ds or read is in ci*/
		printf("OOPS! subject %s can't read object %d :(\n", subject->GetName(), m_name);
		return PermissionDenied;
	}
	/*case 2: Read permission is associate with subject and dataset but not with ci*/
	return Status::Success;
}

ChineseWall::Status ChineseWall::Object::write(const Subject& subject, const uint8_t* buffer, const size_t size)
{
	return ChineseWall::Status();
}
