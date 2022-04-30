#pragma once
#include "Common.h"
/*
* @class DataSet
* @brief This class implements dataset in ChineseWall model
* to read from an object that contains to DS - read approved to the DS before, or read don't approved to the relevant CI
* to write to an object that contains to DS - this is the only DS that the subject can read from
*/
namespace ChineseWall {
	class ConflictInterest;
	class Subject;
	class Dataset {
	public:
		Dataset() = delete;
		/**
		 * constructor
		 * @param name - DS name
		 * @param conflictInterest - CI that contains this DS
		 */
		Dataset(std::string name, ConflictInterest &conflictInterest);
		/**
		 * Try to get read access for subject on the current DS
		 * based on m_accessList
		 *
		 * @param subject - the subject that required the permission
		 * @return Success if permission aproved, PermissionDenied otherwise
		 */
		Status ReadAccess(Subject& subject);
		/**
		 * Try to get write access for subject on the current DS
		 * based on m_accessList
		 *
		 * @param subject - the subject that required the permission
		 * @return Success if permission aproved, PermissionDenied otherwise
		 */
		Status WriteAccess(Subject& subject);
		/**
		 * add specific permission to subject on the current DS
		 *
		 * @param subject - the subject that required the permission
		 * @param permission - required permission
		 * @return Success if succeed, Failure otherwise
		 */
		Status AddPermission(Subject& subject, Permission permission);
		/**
		 * remove specific permission to subject on the current DS
		 *
		 * @param subject - the subject that required the permission
		 * @param permission - required permission
		 * @return Success if succeed, Failure otherwise
		 */
		Status RemovePermission(Subject& subject, Permission permission);
	private:
		std::string m_name;
		ConflictInterest &m_conflictInterest;
		AccessList m_accessList;
	};
}