#include "Object.h"
/*
* @class File
* @brief This class derived from Object in ChineseWall model
* one can read from the file and write to it, based on permission rules.
*/
namespace ChineseWall {
	class File : public Object {
	public:
		/**
		 * constructor
		 * @param name - file name
		 * @param data set- DS that contains the object
		 */
		explicit File(std::string name, Dataset& dataset, Subject& owner);
		/**
		 * default destructor
		 */
		~File() = default;

		/**
		 * Try to read from this object - at first try to get access for reading.
		 *
		 * @param subject - the subject that required the permission
		 * @param position - from where start to read
		 * @param buffer - will contains the readed bytes
		 * @param size - num of bytes to read
		 * @return Success if permission aproved, PermissionDenied otherwise
		 */
		virtual Status Read(Subject & subject, uint8_t position = 0, uint8_t * buffer = 0, const size_t size = 0) override;
		/**
		 * Try to write to this object - at first try to get access for writing.
		 *
		 * @param subject - the subject that required the permission
		 * @param position - start of writing action
		 * @param buffer - data to write
		 * @param size - num of bytes to write
		 * @return Success if permission aproved, PermissionDenied otherwise
		 */
		virtual Status Write(Subject & subject, uint8_t position = 0, const uint8_t * buffer = 0, const size_t size = 0) override;
	private:
		char m_contex[FILE_SIZE] = { 0 };
	};
}