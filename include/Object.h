#pragma once
#include "Common.h"

namespace ChineseWall {
	class Dataset;
	class Subject;
	class Object {
	public:
		explicit Object(std::string name, Dataset &dataset, Subject &owner);
		~Object() = default;

		Status Read(Subject& subject, uint8_t* buffer = 0, const size_t size = 0);
		Status Write(Subject& subject, const uint8_t* buffer = 0, const size_t size = 0);
		Status AddPermission(Subject& subject, Permission permission);
		Status RemovePermission(Subject& subject, Permission permission);
	private:
		Dataset &m_dataset;
		AccessList m_accessList;
		std::string m_name;
	};
}