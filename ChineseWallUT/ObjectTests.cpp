#include "pch.h"
#include "../include/Subject.h"
#include "../include/ConflictInterest.h"
#include "..\include\Dataset.h"
#include "..\include\Object.h"
#include "..\include\File.h"

using namespace ChineseWall;

/* Globals */
const std::string t_subjectName = "sub1";
const std::string t_objName = "obj1";
const std::string t_objName2 = "obj2";
const std::string t_objName3 = "obj3";
const std::string t_dsName = "ds1";
const std::string t_dsName2 = "ds2";
const std::string t_ciName = "ci1";

/* Test Handlers */

/* Tests */
TEST(ObjUT, ObjectGeneral) {
	std::string bufferStr = "Hello World";
	const uint8_t* buffer = reinterpret_cast<const uint8_t*>(bufferStr.c_str());
	uint8_t dataIn[11] = { 0 };
	ConflictInterest t_ci(t_ciName);
	Dataset t_ds(t_dsName, t_ci);
	Dataset t_ds2(t_dsName2, t_ci);
	Subject t_s(t_subjectName);
	File t_obj(t_objName, t_ds, t_s);
	Object t_obj2(t_objName2, t_ds, t_s);
	Object t_obj3(t_objName3, t_ds2, t_s);

	EXPECT_EQ(t_ci.AddPermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_obj.Read(t_s,0, dataIn,0), Status::PermissionDenied);
	EXPECT_EQ(t_ci.RemovePermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_obj.Read(t_s,0, dataIn,0), Status::Success);
	EXPECT_EQ(t_ds.AddPermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_obj.Read(t_s, 0, dataIn, 0), Status::Success);
	EXPECT_EQ(t_obj.AddPermission(t_s, Permission::Read), Status::Success);
	EXPECT_EQ(t_obj.AddPermission(t_s, Permission::Write), Status::Success);
	EXPECT_EQ(t_obj.Read(t_s, 0, dataIn, 0), Status::Success);
	EXPECT_EQ(t_obj2.Read(t_s, 0, dataIn, 0), Status::Success);
	EXPECT_EQ(t_obj3.Read(t_s, 0, dataIn, 0), Status::PermissionDenied);
	EXPECT_EQ(t_obj.Write(t_s,0, buffer, 11), Status::Success);
	EXPECT_EQ(t_obj.Read(t_s,0,dataIn, 11), Status::Success);
	for (int i = 0; i < 11; ++i) {
		EXPECT_EQ(dataIn[i], buffer[i]);
	}

}
