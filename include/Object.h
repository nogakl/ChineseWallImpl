#pragma once
#include "Common.h"

namespace ChineseWall {
	class Dataset;
	class Subject;
	class Object {
	public:
		explicit Object(std::string name, Dataset &dataset, Subject &owner);
		~Object() = default;

		Status read(Subject& subject, uint8_t* buffer, const size_t size);
		Status write(Subject& subject, const uint8_t* buffer, const size_t size);
	private:
		Dataset &m_dataset;
		AccessList m_accsessList;
		std::string m_name;
	};
}