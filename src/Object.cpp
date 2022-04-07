#include "../include/Dataset.h"
#include "../include/Subject.h"
#include "../include/Common.h"
#include "../include/Object.h"

ChineseWall::Object::Object(std::string name, Dataset &dataset, Subject& owner) :
	m_name(name),
	m_dataset(dataset)
{
	m_accsessList.AddPermission(owner.GetName(), Permission::Owner);
}

ChineseWall::Status ChineseWall::Object::read(Subject& subject, uint8_t* buffer, const size_t size)
{
	return m_accsessList.GetAccess(subject.GetName(), Permission::Read) == Status::Success ||
		m_dataset.ReadAccess(subject) == Status::Success ?
		Status::Success :
		Status::PermissionDenied;
}

ChineseWall::Status ChineseWall::Object::write(Subject& subject, const uint8_t* buffer, const size_t size)
{
	return ChineseWall::Status();
}
