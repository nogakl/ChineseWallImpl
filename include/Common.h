#pragma once
#include <cstdint>
#include <map>
#include <list>
#include <memory>
#include <string>

namespace ChineseWall {
	class Subject;
	enum Status : uint8_t {
		Success = 0,
		Failure,
		BadAllocation,
		PermissionDenied
	};
	enum Permission : uint8_t {
		Read = 0,
		Write,
		ReadWrite,
		Execute,
		Owner,
		Delete
	};
	struct AccessList {
	private:
		std::map<std::string, std::list<Permission>> m_accessList;
	public:
		Status GetPermission(std::string subject, Permission permission);
		Status AddPermission(std::string subject, Permission permission);
		Status RemovePermission(std::string subject, Permission permission);
		Status RemoveSubject(std::string subject);
	};
}