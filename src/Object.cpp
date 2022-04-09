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

	Status Object::Read(Subject& subject, uint8_t* buffer, const size_t size)
	{
		if (m_dataset.ReadAccess(subject) == Status::Success) {
			m_accessList.AddPermission(subject.GetName(), Permission::Read);
			return Status::Success;
		}
		return m_accessList.GetPermission(subject.GetName(), Permission::Read);
	}

	Status Object::Write(Subject& subject, const uint8_t* buffer, const size_t size)
	{
		return Status();
	}

	Status Object::AddPermission(Subject& subject, Permission permission)
	{
		return m_accessList.AddPermission(subject.GetName(), permission);
	}

	Status Object::RemovePermission(Subject& subject, Permission permission)
	{
		return m_accessList.RemovePermission(subject.GetName(), permission);
	}
}