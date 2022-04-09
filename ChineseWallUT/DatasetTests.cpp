#include "pch.h"
#include "../include/Subject.h"
#include "../include/ConflictInterest.h"
#include "..\include\Dataset.h"

using namespace ChineseWall;

/* Globals */
const std::string t_subjectName = "sub1";
const std::string t_dsName = "ds1";
const std::string t_ciName = "ci1";

/* Test Handlers */

/* Tests */
TEST(DsUT, DsGeneral) {
	ConflictInterest t_ci(t_ciName);
	Dataset t_ds(t_dsName, t_ci);
	Subject t_s(t_subjectName);
	EXPECT_EQ(t_ci.AddPermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_ds.ReadAccess(t_s), Status::PermissionDenied);
	EXPECT_EQ(t_ci.RemovePermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_ds.ReadAccess(t_s), Status::Success);
	EXPECT_EQ(t_ds.AddPermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_ds.ReadAccess(t_s), Status::Success);
	EXPECT_EQ(t_ci.AddPermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_ds.ReadAccess(t_s), Status::Success);
	EXPECT_EQ(t_ds.WriteAccess(t_s), Status::Success);
}
