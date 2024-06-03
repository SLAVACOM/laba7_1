#pragma once
#include <string>

struct Node {
	std::string fullName;
	int age;
	std::string maritalStatus;
	Node* prev;
	Node* next;
};

namespace constants {
	const std::string fullName{ "Иванов Иван Иванович" };
	const std::string status{ "Не женат" };
	const int age{ 20 };

	const std::string fileName{ "C://Users/slava/source/repos/laba7_1/laba7_1/list.txt" };

}

void addElement(Node*& head, const std::string& fullName, int age, const std::string& maritalStatus);
void printList(Node* head);

bool deleteElement(Node*& head, const std::string& searchValue);
void saveListToFile(Node* head, const std::string& filename);
bool loadListFromFile(Node*& head, const std::string& filename);

void clearList(Node*& head);

bool validAge(std::string age);


void setDefaultValues(Node* head, const std::string& fullName, int age, const std::string& maritalStatus);


void printFunctionsList();

