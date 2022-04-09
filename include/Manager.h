#pragma once
#include "Common.h"
#include "Object.h"
#include "ConflictInterest.h"

namespace ChineseWall {
	class Manager {
	public:
		static Manager& Instance() {
			static Manager instance;
			return instance;
		}
		Status AddSubject(std::string name);
		Status AddObject(std::string name, std::string datasetName, std::string ownerName);
		Status AddDataset(std::string name, std::string conflictInterestName);
		Status AddConflictInterest(std::string name);

	private:
		explicit Manager() {}
		std::map<std::string, std::unique_ptr<Subject>> m_subjects;
		std::map<std::string, std::unique_ptr<Object>> m_objects;
		std::map<std::string, std::unique_ptr<Dataset>> m_datasets;
		std::map<std::string, std::unique_ptr<ConflictInterest>> m_conflictsInterests;
	};
}