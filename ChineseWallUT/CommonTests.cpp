#include "pch.h"

#include "gtest/gtest.h"
#include "../include/Subject.h"
#include "../include/Common.h"

using namespace ChineseWall;

/* Globals */
AccessList t_accList;
const std::string t_subjectName1 = "subject1";

/* Test Handlers */

/* Tests */
TEST(AccessLitstUT, AccListGeneral) {
	EXPECT_EQ(t_accList.GetPermission(t_subjectName1, Permission::Read), Status::PermissionDenied);
	EXPECT_EQ(t_accList.AddPermission(t_subjectName1, Permission::Read), Status::Success);
	EXPECT_EQ(t_accList.GetPermission(t_subjectName1, Permission::Read), Status::Success);
	EXPECT_EQ(t_accList.RemovePermission(t_subjectName1, Permission::Read), Status::Success);
	EXPECT_EQ(t_accList.RemovePermission(t_subjectName1, Permission::Read), Status::Failure);
	EXPECT_EQ(t_accList.RemoveSubject(t_subjectName1), Status::Success);
	EXPECT_EQ(t_accList.RemoveSubject(t_subjectName1), Status::Failure);
}