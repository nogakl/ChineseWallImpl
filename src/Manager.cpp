#include "../include/Subject.h"
#include "../include/Dataset.h"
#include "../include/ConflictInterest.h"
#include "../include/Object.h"
#include "..\include\Manager.h"

namespace ChineseWall {

	Status Manager::AddSubject(std::string name)
	{
		if (m_subjects.at(name) != nullptr) {
			std::pair<std::string, std::unique_ptr<Subject>> newElement = { name, std::make_unique<Subject>(name) };
			return Status::Success;
		}
		printf("Subject already exists!\n");
		return Status::Failure;
	}
	Status Manager::AddObject(std::string name, std::string datasetName, Subject& owner)
	{
		if (m_objects.at(name) != nullptr) {
			if (m_datasets.at(datasetName) == nullptr)
			{
				printf("can't find ds- failed to add object\n");
				return Status::Failure;
			}
			Dataset* ds = m_datasets.at(datasetName).get();
			std::pair<std::string, std::unique_ptr<Object>> newElement = { name, std::make_unique<Object>(name, *ds, owner) };
			return Status::Success;
		}
		printf("Object already exists!\n");
		return Status::Failure;
	}
	Status Manager::AddDataset(std::string name, std::string conflictInterestName)
	{
		if (m_datasets.at(name) != nullptr) {
			if(m_conflictsInterests.at(conflictInterestName) == nullptr)
			{
				printf("can't find ci- failed to add dataset\n");
				return Status::Failure;
			}
			ConflictInterest* ci = m_conflictsInterests.at(conflictInterestName).get();
			std::pair<std::string, std::unique_ptr<Dataset>> newElement = { name, std::make_unique<Dataset>(name, *ci) };
			return Status::Success;
		}
		printf("Dataset already exists!\n");
		return Status::Failure;
	}
	Status Manager::AddConflictInterest(std::string name)
	{
		if (m_conflictsInterests.at(name) != nullptr) {
			std::pair<std::string, std::unique_ptr<ConflictInterest>> newElement = { name, std::make_unique<ConflictInterest>(name) };
			return Status::Success;
		}
		printf("ConflictInterest already exists!\n");
		return Status::Failure;
	}
}