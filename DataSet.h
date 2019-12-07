#ifndef DataSet_h
#define DataSet_h


#include <iostream>
#include "List.h"


using namespace std;

class DataSet
{
public:
	List* listSet;
	DataSet* next;
public:
	DataSet() {

		listSet = new List();
		next = NULL;
	};

};

#endif