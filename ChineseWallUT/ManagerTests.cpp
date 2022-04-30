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
const std::string t_dsName2 = "ds2";
const std::string t_dsName3 = "ds3";
const std::string t_dsName4 = "ds4";
const std::string t_ciName = "ci1";
const std::string t_ciName2 = "ci2";
const std::string t_objName = "obj1";
const std::string t_objName2 = "obj2";
const std::string t_objName3 = "obj3";
const std::string t_objName4 = "obj4";
const std::string t_objName5 = "obj5";
const std::string t_objName6 = "obj6";
Subject* subPtr = nullptr;
Object* objPtr = nullptr;
Object* objPtr2 = nullptr;
Object* objPtr3 = nullptr;
Object* objPtr4 = nullptr;
Object* objPtr5 = nullptr;
Object* objPtr6 = nullptr;

/* Test Handlers */

/* Tests */
TEST(DsUT, ManagerGeneral) {
	EXPECT_EQ(Manager::Instance().AddSubject(t_subjectName), Status::Success);
	EXPECT_EQ(Manager::Instance().AddSubject(t_subjectName), Status::AlreadyExists);
	EXPECT_EQ(Manager::Instance().AddDataset(t_dsName, t_ciName), Status::Failure);
	EXPECT_EQ(Manager::Instance().AddObject(t_objName, FILE_TYPE, t_dsName, t_subjectName), Status::Failure);
	EXPECT_EQ(Manager::Instance().AddConflictInterest(t_ciName), Status::Success);
	EXPECT_EQ(Manager::Instance().AddConflictInterest(t_ciName), Status::AlreadyExists);
	EXPECT_EQ(Manager::Instance().AddDataset(t_dsName, t_ciName), Status::Success);
	EXPECT_EQ(Manager::Instance().AddDataset(t_dsName, t_ciName), Status::AlreadyExists);
	EXPECT_EQ(Manager::Instance().AddObject(t_objName, FILE_TYPE, t_dsName, t_subjectName), Status::Success);
	EXPECT_EQ(Manager::Instance().AddObject(t_objName, FILE_TYPE, t_dsName, t_subjectName), Status::AlreadyExists);

	subPtr = Manager::Instance().GetSubject(t_subjectName);
	EXPECT_EQ(subPtr->AddConflictInterest(t_ciName2), Status::Success);
	EXPECT_EQ(subPtr->AddDataset(t_dsName2, t_ciName), Status::Success);
	EXPECT_EQ(subPtr->AddDataset(t_dsName3, t_ciName2), Status::Success);
	EXPECT_EQ(subPtr->AddDataset(t_dsName4, t_ciName2), Status::Success);
	EXPECT_EQ(subPtr->AddObject(t_objName, FILE_TYPE, t_dsName), Status::AlreadyExists);
	EXPECT_EQ(subPtr->AddObject(t_objName2, FILE_TYPE, t_dsName), Status::Success);
	EXPECT_EQ(subPtr->AddObject(t_objName3, FILE_TYPE, t_dsName2), Status::Success);
	EXPECT_EQ(subPtr->AddObject(t_objName4, FILE_TYPE, t_dsName3), Status::Success);
	EXPECT_EQ(subPtr->AddObject(t_objName5, FILE_TYPE, t_dsName4), Status::Success);
	EXPECT_EQ(subPtr->AddObject(t_objName6, FILE_TYPE, t_dsName4), Status::Success);

	objPtr = Manager::Instance().GetObject(t_objName);
	objPtr2 = Manager::Instance().GetObject(t_objName2);
	objPtr3 = Manager::Instance().GetObject(t_objName3);
	objPtr4 = Manager::Instance().GetObject(t_objName4);
	objPtr5 = Manager::Instance().GetObject(t_objName5);
	objPtr6 = Manager::Instance().GetObject(t_objName6);

	EXPECT_EQ(objPtr->Read(*subPtr), Status::Success);
	EXPECT_EQ(objPtr->Write(*subPtr), Status::Success);
	EXPECT_EQ(objPtr2->Read(*subPtr), Status::Success);
	EXPECT_EQ(objPtr2->Write(*subPtr), Status::Success);
	EXPECT_EQ(objPtr3->Read(*subPtr), Status::PermissionDenied);
	EXPECT_EQ(objPtr3->Write(*subPtr), Status::PermissionDenied);
	EXPECT_EQ(objPtr5->Read(*subPtr), Status::Success);
	EXPECT_EQ(objPtr5->Write(*subPtr), Status::PermissionDenied);
	EXPECT_EQ(objPtr6->Read(*subPtr), Status::Success);
	EXPECT_EQ(objPtr6->Write(*subPtr), Status::PermissionDenied);
	EXPECT_EQ(objPtr4->Read(*subPtr), Status::PermissionDenied);
	EXPECT_EQ(objPtr4->Write(*subPtr), Status::PermissionDenied);

	EXPECT_EQ(Manager::Instance().RemoveObject(t_objName), Status::Success);
	EXPECT_EQ(Manager::Instance().RemoveObject(t_objName2), Status::Success);
	EXPECT_EQ(Manager::Instance().RemoveObject(t_objName3), Status::Success);
	EXPECT_EQ(Manager::Instance().RemoveObject(t_objName4), Status::Success);
	EXPECT_EQ(Manager::Instance().RemoveObject(t_objName5), Status::Success);
	EXPECT_EQ(Manager::Instance().RemoveObject(t_objName6), Status::Success);
	EXPECT_EQ(Manager::Instance().RemoveDataset(t_dsName), Status::Success);
	EXPECT_EQ(Manager::Instance().RemoveDataset(t_dsName2), Status::Success);
	EXPECT_EQ(Manager::Instance().RemoveDataset(t_dsName3), Status::Success);
	EXPECT_EQ(Manager::Instance().RemoveDataset(t_dsName4), Status::Success);
	EXPECT_EQ(Manager::Instance().RemoveConflictInterest(t_ciName), Status::Success);
	EXPECT_EQ(Manager::Instance().RemoveConflictInterest(t_ciName2), Status::Success);







}
