#ifndef List_h
#define List_h

#include "Node.h"
#include <iostream>

using namespace std;

class List {
public:
	Node* head;
public:
	List();
	void display();
};

#endif
