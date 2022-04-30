#pragma once
#include "Common.h"
/*
* @class ConflictInterest
* @brief This class implements conflict interest in ChineseWall model
* to read from an object that contains to CI - read don't approved from this CI
* to write to an object that contains to CI - this is the only CI that the subject can read from
*/
namespace ChineseWall {
	class Subject;
	class ConflictInterest {
	public:
		/**
		 * constructor
		 * @param name - CI name
		 */
		explicit ConflictInterest(std::string name);
		/**
		 * Try to get read access for subject on the current CI
		 * based on m_accessList
		 *
		 * @param subject - the subject that required the permission 
		 * @return Success if permission aproved, PermissionDenied otherwise
		 */
		Status ReadAccess(Subject& subject);
		/**
		 * add specific permission to subject on the current CI
		 *
		 * @param subject - the subject that required the permission
		 * @param permission - required permission
		 * @return Success if succeed, Failure otherwise
		 */
		Status AddPermission(Subject& subject, Permission permission);
		/**
		 * remove specific permission to subject on the current CI
		 *
		 * @param subject - the subject that required the permission
		 * @param permission - required permission
		 * @return Success if succeed, Failure otherwise
		 */
		Status RemovePermission(Subject& subject, Permission permission);
		/**
		 * Try to get write access for subject on the current CI
		 * based on m_accessList
		 *
		 * @param subject - the subject that required the permission
		 * @return Success if permission aproved, PermissionDenied otherwise
		 */
		Status WriteAccess(Subject& subject);
		/**
		 * Get CI name
		 *
		 * @return current CI's name
		 */
		std::string GetName();
	private:
		std::string m_name;
		AccessList m_accessList;
	};
}