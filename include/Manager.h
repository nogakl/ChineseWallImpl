#pragma once
#include "Common.h"
#include "Object.h"
#include "ConflictInterest.h"
/*
* @class Manager
* @brief manage the whole system ie add subject, object, file, thread and more...
* get permissions or remove them...
*/
namespace ChineseWall {
	class Manager {
	public:
		/**
		 * get singeltone instance
		 * retrun static Manager object
		 */
		static Manager& Instance() {
			static Manager instance;
			return instance;
		}
		/**
		 * Add Subject
		 *
		 * @param name - name of subject
		 * @return Status
		 */
		Status AddSubject(std::string name);
		/**
		 * Add Object
		 *
		 * @param name - name of Object
		 * @param type - File or Thread
		 * @param dataset - the DS that contains the object
		 * @param ownerName - the subject that owns the object
		 * @return Status
		 */
		Status AddObject(std::string name, std::string type, std::string datasetName, std::string ownerName);
		/**
		 * Add DS
		 *
		 * @param name - name of DS
		 * @param conflictInterestName - the name of CI that contains the DS
		 * @return Status
		 */
		Status AddDataset(std::string name, std::string conflictInterestName);
		/**
		 * Add CI
		 *
		 * @param name - name of CI
		 * @return Status
		 */
		Status AddConflictInterest(std::string name);
		/**
		 * Remove Subject
		 *
		 * @param name - name of Subject to remove
		 * @return Status
		 */
		Status RemoveSubject(std::string name);
		/**
		 * Remove Object
		 *
		 * @param name - name of Object to remove
		 * @return Status
		 */
		Status RemoveObject(std::string name);
		/**
		 * Remove DS
		 *
		 * @param name - name of DS to remove
		 * @return Status
		 */
		Status RemoveDataset(std::string name);
		/**
		 * Remove CI
		 *
		 * @param name - name of CI to remove
		 * @return Status
		 */
		Status RemoveConflictInterest(std::string name);
		/**
		 * checks if subject has permission only for ciName. 
		 used in get write access
		 *
		 * @param subject - the subject that required the permission
		 * @param permission - relevant permission: read, write...
		 * @param ciName - the name of the CI
		 * @return Success if permission is only for this CI, Failure otherwise.
		 */
		Status IsPermissionExclusive(Subject& subject, Permission permission, std::string ciName);
		/**
		 * Get subject object by its name
		 *
		 * @param name - req name of subject
		 * @return subject object if exists, nullptr otherwise
		 */
		Subject* GetSubject(std::string name);
		/**
		 * Get Object object by its name
		 *
		 * @param name - req name of Object
		 * @return Object object if exists, nullptr otherwise
		 */
		Object* GetObject(std::string name);
		/**
		 * Get DS object by its name
		 *
		 * @param name - req name of DS
		 * @return DS object if exists, nullptr otherwise
		 */
		Dataset* GetDataset(std::string name);
		/**
		 * Get CI object by its name
		 *
		 * @param name - req name of CI
		 * @return CI object if exists, nullptr otherwise
		 */
		ConflictInterest* GetConflictInterest(std::string name);

	private:
		explicit Manager() {}
		std::map<std::string, std::unique_ptr<Subject>> m_subjects;
		std::map<std::string, std::unique_ptr<Object>> m_objects;
		std::map<std::string, std::unique_ptr<Dataset>> m_datasets;
		std::map<std::string, std::unique_ptr<ConflictInterest>> m_conflictsInterests;
	};
}