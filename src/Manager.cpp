#include "Subject.h"
#include "Dataset.h"
#include "ConflictInterest.h"
#include "Object.h"
#include "File.h"
#include "Thread.h"
#include "Manager.h"

namespace ChineseWall {

	Status Manager::AddSubject(std::string name)
	{
		auto it = m_subjects.find(name);
		if (it == m_subjects.end()) {
			m_subjects.insert(std::pair<std::string, std::unique_ptr<Subject>>(name, std::make_unique<Subject>(name)));
			printf("subject %s created!\n", name.c_str());
			return Status::Success;
		}
		printf("Subject %s already exists!\n", name.c_str());
		return Status::AlreadyExists;
	}

	Status Manager::AddObject(std::string name, std::string type, std::string datasetName, std::string ownerName)
	{
		auto itSub = m_subjects.find(ownerName);
		if (itSub == m_subjects.end()) {
			printf("can't find owner name %s. Failed to add Object %s!\n",ownerName.c_str(),name.c_str());
			return Status::Failure;
		}

		Subject& owner = *itSub->second.get();

		auto itObj = m_objects.find(name);
		if (itObj == m_objects.end()) {
			auto itDs = m_datasets.find(datasetName);
			if (itDs == m_datasets.end()) {
				printf("can't find ds %s- failed to add object %s\n", datasetName.c_str(), name.c_str());
				return Status::Failure;
			}
			
			Dataset* ds = m_datasets.at(datasetName).get();
			if (type.compare(FILE_TYPE) == 0)
				m_objects.insert(std::pair<std::string, std::unique_ptr<File>> (name, std::make_unique<File>(name, *ds, owner)));
			else if (type.compare(THREAD_TYPE) == 0)
				m_objects.insert(std::pair<std::string, std::unique_ptr<Thread>>(name, std::make_unique<Thread>(name, *ds, owner)));
			else
				m_objects.insert(std::pair<std::string, std::unique_ptr<Object>>(name, std::make_unique<Object>(name, *ds, owner)));
			printf("Object %s created!\n", name.c_str());
			return Status::Success;
		}
		printf("Object %s already exists!\n", name.c_str());
		return Status::AlreadyExists;
	}
	Status Manager::AddDataset(std::string name, std::string conflictInterestName)
	{
		auto itDs = m_datasets.find(name);
		if (itDs == m_datasets.end()) {
			auto itCi = m_conflictsInterests.find(conflictInterestName);
			if (itCi == m_conflictsInterests.end())
			{
				printf("can't find ci %s- failed to add dataset %s\n", conflictInterestName.c_str(), name.c_str());
				return Status::Failure;
			}
			ConflictInterest* ci = m_conflictsInterests.at(conflictInterestName).get();
			m_datasets.insert(std::pair<std::string, std::unique_ptr<Dataset>>(name, std::make_unique<Dataset>(name, *ci)));
			printf("dataset %s created!\n", name.c_str());
			return Status::Success;
		}
		printf("Dataset %s already exists!\n", name.c_str());
		return Status::AlreadyExists;
	}
	Status Manager::AddConflictInterest(std::string name)
	{
		auto itCi = m_conflictsInterests.find(name);
		if (itCi == m_conflictsInterests.end()) {
			m_conflictsInterests.insert(std::pair<std::string, std::unique_ptr<ConflictInterest>>(name, std::make_unique<ConflictInterest>(name)));
			printf("ConflictInterest %s created!\n", name.c_str());
			return Status::Success;
		}
		printf("ConflictInterest %s already exists!\n", name.c_str());
		return Status::AlreadyExists;
	}
	Status Manager::RemoveSubject(std::string name)
	{
		auto it = m_subjects.find(name);
		if (it != m_subjects.end()) {
			m_subjects.erase(name);
			return Status::Success;
		}
		printf("Subject %s isn't exists!\n",name.c_str());
		return Status::Failure;
	}
	Status Manager::RemoveObject(std::string name)
	{
		auto it = m_objects.find(name);
		if (it != m_objects.end()) {
			m_objects.erase(name);
			return Status::Success;
		}
		printf("Object %s isn't exists!\n", name.c_str());
		return Status::Failure;
	}
	Status Manager::RemoveDataset(std::string name)
	{
		auto it = m_datasets.find(name);
		if (it != m_datasets.end()) {
			m_datasets.erase(name);
			return Status::Success;
		}
		printf("Dataset %s isn't exists!\n", name.c_str());
		return Status::Failure;
	}
	Status Manager::RemoveConflictInterest(std::string name)
	{
		auto it = m_conflictsInterests.find(name);
		if (it != m_conflictsInterests.end()) {
			m_conflictsInterests.erase(name);
			return Status::Success;
		}
		printf("CI %s isn't exists!\n", name.c_str());
		return Status::Failure;
	}
	Status Manager::IsPermissionExclusive(Subject& subject, Permission permission, std::string ciName)
	{
		for (const auto& ci : m_conflictsInterests) {
			auto name = ci.second->GetName();
			if (name != ciName && ci.second->ReadAccess(subject) == Status::Success || name == ciName && ci.second->ReadAccess(subject) != Status::Success)
				return Status::Failure;
		}
		return Status::Success;
	}
	Subject* Manager::GetSubject(std::string name) {
		auto it = m_subjects.find(name);
		if (it == m_subjects.end()) {
			printf("subject %s isn't exists in the system!\n", name.c_str());
			return nullptr;
		}
		return m_subjects.at(name).get();
	}
	Object* Manager::GetObjectCWM(std::string name) {
		auto it = m_objects.find(name);
		if (it == m_objects.end()) {
			printf("object %s isn't exists in the system!\n", name.c_str());
			return nullptr;
		}
		return m_objects.at(name).get();
	}
	Dataset* Manager::GetDataset(std::string name) {
		auto it = m_datasets.find(name);
		if (it == m_datasets.end()) {
			printf("dataset %s isn't exists in the system!\n", name.c_str());
			return nullptr;
		}
		return m_datasets.at(name).get();
	}
	ConflictInterest* Manager::GetConflictInterest(std::string name) {
		auto it = m_conflictsInterests.find(name);
		if (it == m_conflictsInterests.end()) {
			printf("ci %s isn't exists in the system!\n", name.c_str());
			return nullptr;
		}
		return m_conflictsInterests.at(name).get();
	}
}