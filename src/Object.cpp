#include "../include/Dataset.h"
#include "../include/Subject.h"
#include "../include/Common.h"
#include "../include/Object.h"
namespace ChineseWall {
	Object::Object(std::string name, Dataset& dataset, Subject& owner) :
		m_name(name),
		m_dataset(dataset)
	{
		m_accessList.AddPermission(owner.GetName(), Permission::Owner);
	}

	Status Object::Read(Subject& subject, uint8_t position, uint8_t* buffer, const size_t size)
	{
		return m_accessList.GetPermission(subject.GetName(), Permission::Read) != Status::Success ?
			m_dataset.ReadAccess(subject) == Status::Success ? AddPermission(subject, Permission::Read) : Status::PermissionDenied :
			Status::Success;
	}

	Status Object::Write(Subject& subject, uint8_t position, const uint8_t* buffer, const size_t size)
	{
		return m_accessList.GetPermission(subject.GetName(), Permission::Write) != Status::Success ?
			Read(subject) == Status::Success && m_dataset.WriteAccess(subject) == Status::Success ? AddPermission(subject, Permission::Write) : Status::PermissionDenied :
			Status::Success;
	}

	Status Object::AddPermission(Subject& subject, Permission permission)
	{
		return m_dataset.AddPermission(subject, permission) == Status::Success ?
			m_accessList.AddPermission(subject.GetName(), permission) :
			Status::Failure;
	}

	Status Object::RemovePermission(Subject& subject, Permission permission)
	{
		return m_accessList.RemovePermission(subject.GetName(), permission);
	}
}