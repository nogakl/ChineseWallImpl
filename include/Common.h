#pragma once
#include <cstdint>
#include <map>
#include <list>
#include <memory>
#include <string>

namespace ChineseWall {
	const std::string FILE_TYPE = "File";
	const std::string THREAD_TYPE = "Thread";
	static constexpr int FILE_SIZE = 128;
	static constexpr int THREAD_MEMORY_SPACE = 256;
	class Subject;
	enum class Status : uint8_t {
		Success = 0,
		Failure,
		BadAllocation,
		PermissionDenied,
		AlreadyExists,
		InvalidArguments
	};
	enum class Permission : uint8_t {
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