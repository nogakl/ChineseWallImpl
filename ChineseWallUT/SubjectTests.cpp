#include "pch.h"
#include "gtest/gtest.h"
#include "../include/Subject.h"
#include "../include/Common.h"

using namespace ChineseWall;

/* Globals */
const std::string t_subjectName1 = "testSubject";
const std::string t_subjectName2 = "testSubject2";
const std::string t_ciName = "ci";
const std::string t_ciName2 = "ci2";
const std::string t_dsName = "ds";
const std::string t_dsName2 = "ds2";
const std::string t_objectName = "obj";

/* Test Handlers */

/* Tests */
TEST(SubjectUT, GetName) {
	Subject s(t_subjectName1);
	EXPECT_EQ(s.GetName(), t_subjectName1);
}

TEST(SubjectUT, Add) {
	Subject s(t_subjectName1);
	EXPECT_EQ(s.AddSubject(t_subjectName1), Status::Success);
	EXPECT_EQ(s.AddSubject(t_subjectName2), Status::Success);
	EXPECT_EQ(s.AddSubject(t_subjectName2), Status::Failure);
	EXPECT_EQ(s.AddConflictInterest(t_ciName), Status::Success);
	EXPECT_EQ(s.AddConflictInterest(t_ciName), Status::Failure);
	EXPECT_EQ(s.AddDataset(t_dsName, t_ciName), Status::Success);
	EXPECT_EQ(s.AddDataset(t_dsName, t_ciName), Status::Failure);
	EXPECT_EQ(s.AddDataset(t_dsName, t_ciName2), Status::Failure);
	EXPECT_EQ(s.AddObject(t_objectName, t_dsName), Status::Success);
	EXPECT_EQ(s.AddObject(t_objectName, t_dsName), Status::Failure);
	EXPECT_EQ(s.AddObject(t_objectName, t_dsName2), Status::Failure);
}