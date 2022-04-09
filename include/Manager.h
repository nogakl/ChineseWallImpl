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
		Status RemoveSubject(std::string name);
		Status RemoveObject(std::string name);
		Status RemoveDataset(std::string name);
		Status RemoveConflictInterest(std::string name);
		Status IsPermissionExclusive(Subject& subject, Permission permission, std::string ciName);
		Subject* GetSubject(std::string name);
		Object* GetObject(std::string name);
		Dataset* GetDataset(std::string name);
		ConflictInterest* GetConflictInterest(std::string name);

	private:
		explicit Manager() {}
		std::map<std::string, std::unique_ptr<Subject>> m_subjects;
		std::map<std::string, std::unique_ptr<Object>> m_objects;
		std::map<std::string, std::unique_ptr<Dataset>> m_datasets;
		std::map<std::string, std::unique_ptr<ConflictInterest>> m_conflictsInterests;
	};
}