#include "Dataset.h"
#include "Subject.h"
#include "Common.h"
#include "Thread.h"

namespace ChineseWall {
	Thread::Thread(std::string name, Dataset& dataset, Subject& owner) :
		Object(name, dataset, owner)
	{}
	Status Thread::Read(Subject& subject, uint8_t position, uint8_t* buffer, const size_t size) {
		if (buffer == nullptr || position + size > FILE_SIZE)
			return Status::InvalidArguments;

		auto stat = Object::Read(subject);
		if (stat == Status::Success)
		{
			for (int i = 0; i < size; ++i) {
				buffer[i] = m_memory[position + i];
			}
		}
		return stat;
	}
	Status Thread::Write(Subject& subject, uint8_t position, const uint8_t* buffer, const size_t size) {
		if (buffer == nullptr || position + size > FILE_SIZE)
			return Status::InvalidArguments;

		auto stat = Object::Write(subject);
		if (stat == Status::Success)
		{
			for (int i = 0; i < size; ++i) {
				m_memory[position + i] = buffer[i];
			}
		}
		return stat;
	}
}