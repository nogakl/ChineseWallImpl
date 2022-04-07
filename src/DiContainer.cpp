#include "..\include\DiContainer.h"

namespace ChineseWall {

	Status Manager::AddSubject(std::string name)
	{
		if (m_subjects.at(name) != nullptr) {
			std::pair<std::string, std::shared_ptr<Subject>> newElement = { name, std::make_shared<Subject>(name) };
			return Status::Success;
		}
		printf("Subject already exists!\n");
		return Status::Failure;
	}
	Status Manager::AddObject(std::string name, std::string datasetName, const Subject& owner)
	{
		if (m_objects.at(name) != nullptr) {
			auto ds = m_datasets.at(datasetName);
			if (ds == nullptr)
			{
				printf("can't find ds- failed to add object\n");
				return Status::Failure;
			}
			std::pair<std::string, std::shared_ptr<Object>> newElement = { name, std::make_shared<Object>(name, std::move(ds), owner) };
			return Status::Success;
		}
		printf("Object already exists!\n");
		return Status::Failure;
	}
	Status Manager::AddDataset(std::string name, std::string conflictInterestName)
	{
		if (m_datasets.at(name) != nullptr) {
			auto ci = m_conflictsInterests.at(conflictInterestName);
			if (ci == nullptr)
			{
				printf("can't find ci- failed to add dataset\n");
				return Status::Failure;
			}
			std::pair<std::string, std::shared_ptr<Dataset>> newElement = { name, std::make_shared<Dataset>(name, std::move(ci)) };
			return Status::Success;
		}
		printf("Dataset already exists!\n");
		return Status::Failure;
	}
	Status Manager::AddConflictInterest(std::string name)
	{
		if (m_conflictsInterests.at(name) != nullptr) {
			std::pair<std::string, std::shared_ptr<ConflictInterest>> newElement = { name, std::make_shared<ConflictInterest>(name) };
			return Status::Success;
		}
		printf("ConflictInterest already exists!\n");
		return Status::Failure;
	}
}