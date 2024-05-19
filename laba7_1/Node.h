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
    const std::string fullName{ "������ ���� ��������" };
    const std::string status{ "������" };
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

/*������ ���� ��������; 30; ������
������ ���� ��������; 40; �����
������� ����� ���������; 25; ������
�������� ������� ����������; 35; �����
����� ������ ���������; 28; ������
�������� ������� ����������; 50; �����
*/