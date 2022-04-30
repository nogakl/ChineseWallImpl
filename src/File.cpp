#include "../include/Dataset.h"
#include "../include/Subject.h"
#include "../include/Common.h"
#include "../include/File.h"

namespace ChineseWall {
    File::File(std::string name, Dataset& dataset, Subject& owner) :
        Object(name, dataset, owner) { }

    Status File::Read(Subject& subject, uint8_t position, uint8_t* buffer, const size_t size)
    {
        if (buffer == nullptr || position + size > FILE_SIZE)
            return Status::InvalidArguments;

        auto stat = Object::Read(subject);
        if (stat == Status::Success)
        {
            for (int i = 0; i < size; ++i) {
                buffer[i] = m_contex[position + i];
            }
        }
        return stat;
    }
    Status File::Write(Subject& subject, uint8_t position, const uint8_t* buffer, const size_t size) {
        if (buffer == nullptr || position + size > FILE_SIZE)
            return Status::InvalidArguments;
        auto stat = Object::Write(subject);
        if (stat == Status::Success)
        {
            for (int i = 0; i < size; ++i) {
                m_contex[position + i] = buffer[i];
            }
        }
        return stat;
    }
}