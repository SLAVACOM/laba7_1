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
    const std::string status{ "Холост" };
    const int age { 20 };
}

void addElement(Node*& head, const std::string& fullName, int age, const std::string& maritalStatus);
void printList(Node* head);

bool isElementInList(Node* head, const std::string& searchValue);
bool deleteElement(Node*& head, const std::string& searchValue);
void saveListToFile(Node* head, const std::string& filename);
bool loadListFromFile(Node*& head, const std::string& filename);

void clearList(Node*& head);

int getIntInput();

void setDefaultValues(Node* head, const std::string& fullName, int age, const std::string& maritalStatus);

void  printFunctionsList();

/*Иванов Иван Иванович; 30; Холост
Петров Петр Петрович; 40; Женат
Сидоров Сидор Сидорович; 25; Холост
Кузнецов Алексей Алексеевич; 35; Женат
Попов Сергей Сергеевич; 28; Холост
Васильев Василий Васильевич; 50; Женат
*/