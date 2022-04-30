#pragma once
#include "Common.h"
/*
* @class Subject
* @brief This class implements subject in CheinesWall model - 
* each instance has its name and can do some actions, as add another subject to the system (and become its owner).
*/
namespace ChineseWall {
	class Subject {
	public:
		/**
		 * constructor
		 * @param name - file name
		 * @param data set- DS that contains the object
		 */
		explicit Subject(std::string name);
		/**
		 * default destructor
		 */
		~Subject();
		/**
		 * Add subject to the system
		 *
		 * @param name - subject name
		 * @return Status
		 */
		Status AddSubject(std::string name);
		/**
		 * Add Object to the system
		 *
		 * @param name - Object name
		 * @param type - File or Thread
		 * @param DS - DS that contains the object
		 * @return Status
		 */
		Status AddObject(std::string name, std::string type, std::string datasetName);
		/**
		 * Add DS to the system
		 *
		 * @param name - DS name
		 * @param CI - CI that contains the DS
		 * @return Status
		 */
		Status AddDataset(std::string name, std::string ciName);
		/**
		 * Add CI to the system
		 * 
		 * @param name - CI name
		 * @return Status
		 */
		Status AddConflictInterest(std::string name);
		/**
		 * 
		 * Get subject name
		 *
		 * @return string of current subject name
		 */
		std::string GetName();
	private:
		std::string m_name; 
	};
}