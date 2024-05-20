#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <limits>


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
    if (!inFile) {
        std::cerr << "������ �������� ����� ��� ������" << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream ss(line);
        std::string fullName, maritalStatus;
        int age;
        char delimiter;

        std::getline(ss, fullName, ';');
        ss >> age >> delimiter;
        std::getline(ss, maritalStatus);

        addElement(head, fullName, age, maritalStatus);
    }

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

int getIntInput() {
    int input;
    while (!(std::cin >> input)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "������������ ����. ����������, ������� ����� �����: ";
    }
    return input;
}

void printFunctionsList() {
    std::cout << "1)������� �������� �������\n2)������ ���� ���������" << std::endl;
    std::cout << "3)���������� ���� ��������� ����������������� ��������" << std::endl;
    std::cout << "4)�������� ������ (�������� � �����)\n5)�����" << std::endl;
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

void setList(Node* &head, const std::string& filename) {
    clearList(head);
    addElement(head, "����� �������", 35, "�� �������");
    addElement(head, "������ ������", 42, "�����");
    addElement(head, "��������� ��������", 28, "�� �������");
    addElement(head, "��������� ��������", 39, "�����");
    addElement(head, "����� ��������", 31, "�� �������");
    addElement(head, "������� �������", 27, "�� �����");
    addElement(head, "���� ��������", 24, "�� �������");
    addElement(head, "������ �����", 45, "�����");
    addElement(head, "����� ��������", 33, "�� �������");
    addElement(head, "���� �����", 29, "�� �����");
    saveListToFile(head, filename);
}
