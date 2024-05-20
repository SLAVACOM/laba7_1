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
}

void addElement(Node*& head, const std::string& fullName, int age, const std::string& maritalStatus);
void printList(Node* head);

bool deleteElement(Node*& head, const std::string& searchValue);
void saveListToFile(Node* head, const std::string& filename);
bool loadListFromFile(Node*& head, const std::string& filename);

void clearList(Node*& head);

int getIntInput();

void setDefaultValues(Node* head, const std::string& fullName, int age, const std::string& maritalStatus);


void setList(Node*& head, const std::string& filename);

void printFunctionsList();

