#include "List.h"
#include "Node.h"

List::List() {

	head = NULL;

};

void List::display() {
	Node* displaynode = head;
	if (displaynode == NULL) {
		cout << "Empty list is provided" << endl;
	}
	while (displaynode != NULL) {
		cout << displaynode->ID << "\t" << displaynode->JobTitle << "\t" << displaynode->EmailAddress << "\t" << displaynode->LastName << "\t"
			<< displaynode->FirstName << "\t" << displaynode->PhoneNumber << "\t" << displaynode->Skills << "\t" << displaynode->Country << "\n";
		cout << endl;
	}
	cout << endl;
}



