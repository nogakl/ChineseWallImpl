#pragma once
#include "Common.h"

namespace ChineseWall {
	class Dataset;
	class Subject;
	class Object {
	public:
		/**
		 * constructor
		 * @param name - object name
		 * @param data set- DS that contains the object
		 */
		explicit Object(std::string name, Dataset &dataset, Subject &owner);
		/**
		 * default destructor
		 */
		~Object() = default;

		/**
		 * Try to read from this object - at first try to get access for reading.
		 *
		 * @param subject - the subject that required the permission
		 * @param buffer - will contains the readed bytes
		 * @param size - num of bytes to read
		 * @return Success if permission aproved, PermissionDenied otherwise
		 */
		virtual Status Read(Subject& subject, uint8_t position = 0, uint8_t* buffer = 0, const size_t size = 0);
		/**
		 * Try to write to this object - at first try to get access for writing.
		 *
		 * @param subject - the subject that required the permission
		 * @param buffer - data to write
		 * @param size - num of bytes to write
		 * @return Success if permission aproved, PermissionDenied otherwise
		 */
		virtual Status Write(Subject& subject, uint8_t position = 0, const uint8_t* buffer = 0, const size_t size = 0);
		/**
		 * add permission to subject on current object.
		 *
		 * @param subject - the subject that required the permission
		 * @param permission 
		 * @return Success if permission aproved, Failure otherwise
		 */
		Status AddPermission(Subject& subject, Permission permission);
		/**
		 * remove permission to subject on current object.
		 *
		 * @param subject - the subject that required the permission
		 * @param permission
		 * @return Success if permission exists, Failure otherwise
		 */
		Status RemovePermission(Subject& subject, Permission permission);
	private:
		Dataset &m_dataset;
		AccessList m_accessList;
		std::string m_name;
	};
}