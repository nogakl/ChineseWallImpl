#include "pch.h"
#include "../include/Subject.h"
#include "../include/ConflictInterest.h"
#include "..\include\Dataset.h"
#include "..\include\Object.h"

using namespace ChineseWall;

/* Globals */
const std::string t_subjectName = "sub1";
const std::string t_objName = "obj1";
const std::string t_dsName = "ds1";
const std::string t_ciName = "ci1";

/* Test Handlers */

/* Tests */
TEST(ObjUT, DsGeneral) {
	ConflictInterest t_ci(t_ciName);
	Dataset t_ds(t_dsName, t_ci);
	Subject t_s(t_subjectName);
	Object t_obj(t_objName, t_ds, t_s);

	EXPECT_EQ(t_ci.AddPermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_obj.Read(t_s, 0, 0), Status::PermissionDenied);
	EXPECT_EQ(t_ci.RemovePermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_obj.Read(t_s, 0, 0), Status::Success);
	EXPECT_EQ(t_ds.AddPermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_obj.Read(t_s, 0, 0), Status::Success);
	EXPECT_EQ(t_obj.AddPermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_obj.Read(t_s, 0, 0), Status::Success);
}
