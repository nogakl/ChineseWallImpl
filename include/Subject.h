#pragma once
#include "Common.h"
namespace ChineseWall {
	class Subject {
	public:
		explicit Subject(std::string name);
		~Subject();
		Status AddSubject(std::string name);
		Status AddObject(std::string name, std::string datasetName);
		Status AddDataset(std::string name, std::string ciName);
		Status AddConflictInterest(std::string name);
		std::string GetName();
	private:
		std::string m_name; 
	};
}