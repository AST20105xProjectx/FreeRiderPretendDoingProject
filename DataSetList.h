#ifndef DataSetList_h
#define DataSetList_h

#include "DataSet.h"
#include <iostream>

using namespace std;

class DataSetList
{
public:
	DataSet* DataSetHead;
public:
	DataSetList();
	void fileinput();

	void MainMenu();

	void SearchingMenu();
	void SearchingByID();
	void SearchingBySkills();
	void SearchingByJobTitle();
	void SearchingByCountry();
	
	void SearchingBySkillsxJobTitle();
	void SearchingBySkillsxCountry();
	void SearchingBySkillsxID();	
	void SearchingByJobTitlexCountry();
	void SearchingByJobTitlexID();
	void SearchingByCountryxID();

	void DeletionMenu();
	void DeletionByPhoneNumber();
	void DeletionByCountry();
};

#endif