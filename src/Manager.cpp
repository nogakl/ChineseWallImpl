#include "../include/Subject.h"
#include "../include/Dataset.h"
#include "../include/ConflictInterest.h"
#include "../include/Object.h"
#include "..\include\Manager.h"

namespace ChineseWall {

	Status Manager::AddSubject(std::string name)
	{
		auto it = m_subjects.find(name);
		if (it == m_subjects.end()) {
			m_subjects.insert(std::pair<std::string, std::unique_ptr<Subject>>(name, std::make_unique<Subject>(name)));
			return Status::Success;
		}
		printf("Subject already exists!\n");
		return Status::AlreadyExists;
	}

	Status Manager::AddObject(std::string name, std::string datasetName, std::string ownerName)
	{
		auto itSub = m_subjects.find(ownerName);
		if (itSub == m_subjects.end()) {
			printf("can't find owner name. Failed to add Object!\n");
			return Status::Failure;
		}

		Subject& owner = *itSub->second.get();

		auto itObj = m_objects.find(name);
		if (itObj == m_objects.end()) {
			auto itDs = m_datasets.find(datasetName);
			if (itDs == m_datasets.end()) {
				printf("can't find ds- failed to add object\n");
				return Status::Failure;
			}
			Dataset* ds = m_datasets.at(datasetName).get();
			m_objects.insert(std::pair<std::string, std::unique_ptr<Object>>(name, std::make_unique<Object>(name, *ds, owner)));
			return Status::Success;
		}
		printf("Object already exists!\n");
		return Status::AlreadyExists;
	}
	Status Manager::AddDataset(std::string name, std::string conflictInterestName)
	{
		auto itDs = m_datasets.find(name);
		if (itDs == m_datasets.end()) {
			auto itCi = m_conflictsInterests.find(conflictInterestName);
			if (itCi == m_conflictsInterests.end())
			{
				printf("can't find ci- failed to add dataset\n");
				return Status::Failure;
			}
			ConflictInterest* ci = m_conflictsInterests.at(conflictInterestName).get();
			m_datasets.insert(std::pair<std::string, std::unique_ptr<Dataset>>(name, std::make_unique<Dataset>(name, *ci)));
			return Status::Success;
		}
		printf("Dataset already exists!\n");
		return Status::AlreadyExists;
	}
	Status Manager::AddConflictInterest(std::string name)
	{
		auto itCi = m_conflictsInterests.find(name);
		if (itCi == m_conflictsInterests.end()) {
			m_conflictsInterests.insert(std::pair<std::string, std::unique_ptr<ConflictInterest>>(name, std::make_unique<ConflictInterest>(name)));
			return Status::Success;
		}
		printf("ConflictInterest already exists!\n");
		return Status::AlreadyExists;
	}
	Status Manager::RemoveSubject(std::string name)
	{
		auto it = m_subjects.find(name);
		if (it != m_subjects.end()) {
			m_subjects.erase(name);
			return Status::Success;
		}
		printf("Subject isn't exists!\n");
		return Status::Failure;
	}
	Status Manager::RemoveObject(std::string name)
	{
		auto it = m_objects.find(name);
		if (it != m_objects.end()) {
			m_objects.erase(name);
			return Status::Success;
		}
		printf("Object isn't exists!\n");
		return Status::Failure;
	}
	Status Manager::RemoveDataset(std::string name)
	{
		auto it = m_datasets.find(name);
		if (it != m_datasets.end()) {
			m_datasets.erase(name);
			return Status::Success;
		}
		printf("Dataset isn't exists!\n");
		return Status::Failure;
	}
	Status Manager::RemoveConflictInterest(std::string name)
	{
		auto it = m_conflictsInterests.find(name);
		if (it != m_conflictsInterests.end()) {
			m_conflictsInterests.erase(name);
			return Status::Success;
		}
		printf("CI isn't exists!\n");
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
			printf("subject isn't exists in the system!");
			return nullptr;
		}
		return m_subjects.at(name).get();
	}
	Object* Manager::GetObject(std::string name) {
		auto it = m_objects.find(name);
		if (it == m_objects.end()) {
			printf("object isn't exists in the system!");
			return nullptr;
		}
		return m_objects.at(name).get();
	}
	Dataset* Manager::GetDataset(std::string name) {
		auto it = m_datasets.find(name);
		if (it == m_datasets.end()) {
			printf("dataset isn't exists in the system!");
			return nullptr;
		}
		return m_datasets.at(name).get();
	}
	ConflictInterest* Manager::GetConflictInterest(std::string name) {
		auto it = m_conflictsInterests.find(name);
		if (it == m_conflictsInterests.end()) {
			printf("ci isn't exists in the system!");
			return nullptr;
		}
		return m_conflictsInterests.at(name).get();
	}
}