#ifndef Node_h
#define Node_h

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Node
{
public:
	string ID;
	string JobTitle;
	string EmailAddress;
	string LastName;
	string FirstName;
	string PhoneNumber;
	string Skills;
	string Country;
	Node* next;

public:
	Node(string ID, string JobTitle, string EmailAddress, string LastName, string FirstName, string PhoneNumber, string Skills, string Country)
	{
		this->ID = ID;
		this->JobTitle = JobTitle;
		this->EmailAddress = EmailAddress;
		this->LastName = LastName;
		this->FirstName = FirstName;
		this->PhoneNumber = PhoneNumber;
		this->Skills = Skills;
		this->Country = Country;
		this->next = NULL;
	};
};

#endif