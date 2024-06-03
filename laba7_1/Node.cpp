#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <limits>
#include <regex>


void addElement(Node*& head, const std::string& fullName, int age, const std::string& maritalStatus) {
	Node* newNode = new Node{ fullName, age, maritalStatus, nullptr, nullptr };
	if (!newNode) {
		throw std::runtime_error("Memory allocation failed");
	}
	if (!head) {
		head = newNode;
		head->next = head;
		head->prev = head;
	}
	else {
		Node* tail = head->prev;
		tail->next = newNode;
		newNode->prev = tail;
		newNode->next = head;
		head->prev = newNode;
	}
}

void printList(Node* head) {
	if (!head) {
		std::cout << "������ ����" << std::endl;
		return;
	}

	Node* current = head;
	std::cout << "������" << std::endl;
	do {
		std::cout << "���: " << current->fullName << ", �������: " << current->age << ", �������� ���������: " << current->maritalStatus << std::endl;
		current = current->next;
	} while (current != head);
	std::cout << std::endl;
}

void saveListToFile(Node* head, const std::string& filename) {
	std::ofstream outFile(filename);
	if (!outFile) {
		std::cerr << "������ �������� ����� ��� ������" << std::endl;
		return;
	}
	if (!head) {
		outFile << "";
		return;
	}
	Node* current = head;
	do {
		outFile << current->fullName << "; " << current->age << "; " << current->maritalStatus << "\n";
		current = current->next;
	} while (current != head);
}

bool loadListFromFile(Node*& head, const std::string& filename) {
	std::ifstream inFile(filename);
	if (!inFile.is_open()) {
		std::cerr << "������ �������� ����� ��� ������" << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(inFile, line)) {
		try {
			std::istringstream iss(line);

			std::string fullName, maritalStatus, age;

			std::getline(iss, fullName, ';');
			std::getline(iss, age, ';');
			std::getline(iss, maritalStatus, ';');

			if (!fullName.empty() && validAge(age) && !maritalStatus.empty()) {
				addElement(head, fullName, std::stoi(age), maritalStatus);
			}
			else if (line.empty()) return true;
			else return false;
		}
		catch (const std::exception& e) {
			std::cerr << "������ �������� � �����" << std::endl;
			return false;
		}
	}
	inFile.close();
	return true;
}

void clearList(Node*& head) {
	if (!head) return;

	Node* current = head;
	do {
		Node* temp = current;
		current = current->next;
		delete temp;
	} while (current != head);

	head = nullptr;
}

bool validAge(std::string age) {
	std::regex valid_age("[1-9][0-9]?[0-9]?|0");
	return regex_match(age, valid_age);
}
void printFunctionsList() {
	std::cout << "1)������� �������� �������\n2)������ ���� ���������" << std::endl;
	std::cout << "3)���������� ���� ��������� ����������������� ��������" << std::endl;
	std::cout << "4)�����" << std::endl;
}

bool deleteElement(Node*& head, const std::string& searchValue) {
	if (!head) return false;

	Node* current = head;
	do {
		if (current->fullName == searchValue) {
			if (current->next && current->prev == current) {
				delete current;
				head = nullptr;
				return true;
			}

			Node* prevNode = current->prev;
			Node* nextNode = current->next;

			prevNode->next = nextNode;
			nextNode->prev = prevNode;

			if (current == head) {
				head = nextNode;
			}

			delete current;
			std::cout << "������� �������" << std::endl;
			return true;
		}
		current = current->next;
	} while (current != head);

	return false;
}

void setDefaultValues(Node* head, const std::string& fullName, int age, const std::string& maritalStatus) {
	if (!head) return;

	Node* current = head;
	do {
		current->fullName = fullName;
		current->age = age;
		current->maritalStatus = maritalStatus;
		current = current->next;
	} while (current != head);
}

