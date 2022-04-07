#include "../include/Common.h"
#include "../include/Dataset.h"
#include "../include/Object.h"

ChineseWall::Object::Object(std::string name, std::unique_ptr<Dataset> dataset, Subject& owner) :
	m_name(name),
	m_dataset(std::move(dataset))
{
	m_accsessList.AddPermission(owner, Permission::Owner);
}

ChineseWall::Status ChineseWall::Object::read(const Subject& subject, uint8_t* buffer, const size_t size)
{
	return m_accsessList.GetAccess(subject, Permission::Read) == Status::Success ||
		m_dataset->ReadAccess(subject) == Status::Success ?
		Status::Success :
		Status::PermissionDenied;
}

ChineseWall::Status ChineseWall::Object::write(const Subject& subject, const uint8_t* buffer, const size_t size)
{
	return ChineseWall::Status();
}
