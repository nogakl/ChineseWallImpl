#include "..\include\Dataset.h"
#include "..\include\Manager.h"
#include "..\include\Subject.h"

namespace ChineseWall {
    Subject::Subject(std::string name) :
        m_name(name) { }

    Subject::~Subject() = default;

    Status Subject::AddSubject(std::string name)
    {
        return Manager::Instance().AddSubject(name);
    }

    Status Subject::AddObject(std::string name, std::string datasetName)
    {
        return Manager::Instance().AddObject(name, datasetName, *this);
    }

    Status Subject::AddDataset(std::string name, std::string ciName)
    {
        return Manager::Instance().AddDataset(name, ciName);
    }

    Status Subject::AddConflictInterest(std::string name)
    {
        return Manager::Instance().AddConflictInterest(name);
    }
    std::string Subject::GetName()
    {
        return m_name;
    }
}