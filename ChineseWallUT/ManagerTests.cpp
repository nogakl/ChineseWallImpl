#include "pch.h"
#include "../include/Subject.h"
#include "../include/Dataset.h"
#include "../include/ConflictInterest.h"
#include "../include/Object.h"
#include "../include/Manager.h"

using namespace ChineseWall;

/* Globals */
const std::string t_subjectName = "sub1";
const std::string t_dsName = "ds1";
const std::string t_ciName = "ci1";
const std::string t_objName = "obj1";

/* Test Handlers */

/* Tests */
TEST(DsUT, ManagerGeneral) {
	EXPECT_EQ(Manager::Instance().AddSubject(t_subjectName), Status::Success);
	EXPECT_EQ(Manager::Instance().AddSubject(t_subjectName), Status::Failure);
	EXPECT_EQ(Manager::Instance().AddDataset(t_dsName, t_ciName), Status::Failure);
	EXPECT_EQ(Manager::Instance().AddObject(t_objName, t_dsName, t_subjectName), Status::Failure);
	EXPECT_EQ(Manager::Instance().AddConflictInterest(t_ciName), Status::Success);
	EXPECT_EQ(Manager::Instance().AddConflictInterest(t_ciName), Status::Failure);
	EXPECT_EQ(Manager::Instance().AddDataset(t_dsName, t_ciName), Status::Success);
	EXPECT_EQ(Manager::Instance().AddDataset(t_dsName, t_ciName), Status::Failure);
	EXPECT_EQ(Manager::Instance().AddObject(t_objName, t_dsName, t_subjectName), Status::Success);
	EXPECT_EQ(Manager::Instance().AddObject(t_objName, t_dsName, t_subjectName), Status::Failure);
}
