#pragma once
#include <memory>
#include <map>
#include <list>
#include <string>
#include "Status.h"
#include "Permissions.h"

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
		std::map<Subject, std::unique_ptr<std::list<Permission>>> m_accessList;
		std::string m_name;
	};
}