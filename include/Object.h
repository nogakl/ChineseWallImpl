#pragma once
#include "Common.h"

namespace ChineseWall {
	class Dataset;
	class Subject;
	class Object {
	public:
		explicit Object(std::string name, std::unique_ptr<Dataset> dataset, Subject &owner);
		~Object() = default;

		Status read(const Subject& subject, uint8_t* buffer, const size_t size);
		Status write(const Subject& subject, const uint8_t* buffer, const size_t size);
	private:
		std::unique_ptr<Dataset> m_dataset;
		AccessList m_accsessList;
		std::string m_name;
	};
}