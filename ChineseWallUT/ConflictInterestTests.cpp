#include "pch.h"
#include "../include/Subject.h"
#include "..\include\ConflictInterest.h"

using namespace ChineseWall;

/* Globals */
const std::string t_subjectName = "sub1";
const std::string t_ciName = "ci1";

/* Test Handlers */

/* Tests */
TEST(CiUT, CiGeneral) {
	ConflictInterest t_ci(t_ciName);
	Subject t_s(t_subjectName);

	EXPECT_EQ(t_ci.ReadAccess(t_s), Status::PermissionDenied);
	EXPECT_EQ(t_ci.AddPermission(t_s, Permission::Execute), Status::Success);
	EXPECT_EQ(t_ci.ReadAccess(t_s), Status::PermissionDenied);
	EXPECT_EQ(t_ci.AddPermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_ci.ReadAccess(t_s), Status::Success);
	EXPECT_EQ(t_ci.RemovePermission(t_s, Permission::Execute), Status::Success);
	EXPECT_EQ(t_ci.RemovePermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_ci.RemovePermission(t_s, Permission::Read), Status::Failure);
	EXPECT_EQ(t_ci.ReadAccess(t_s), Status::PermissionDenied);
}
