#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include <limits>


void addElement(Node*& head, const std::string& fullName, int age, const std::string& maritalStatus) {
    Node* newNode = new Node{ fullName, age, maritalStatus, nullptr, nullptr };

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
        std::cout << "Список пуст" << std::endl;
        return;
    }

    Node* current = head;
    std::cout << "Список" << std::endl;
    do {
        std::cout << "ФИО: " << current->fullName << ", Возраст: " << current->age << ", Семейное положение: " << current->maritalStatus << std::endl;
        current = current->next;
    } while (current != head);
    std::cout << std::endl;
}

bool isElementInList(Node* head, const std::string& searchValue) {
    if (!head) return false;

    Node* current = head;
    do {
        if (current->fullName == searchValue) {
            return true;
        }
        current = current->next;
    } while (current != head);

    return false;
}

void saveListToFile(Node* head, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Ошибка открытия файла для записи" << std::endl;
        return;
    }

    Node* current = head;
    do {
        outFile << current->fullName << " ;" << current->age << " ;" << current->maritalStatus << "\n";
        current = current->next;
    } while (current != head);
}

bool loadListFromFile(Node*& head, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Ошибка открытия файла для чтения" << std::endl;
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
        std::cout << "Некорректный ввод. Пожалуйста, введите целое число: ";
    }
    return input;
}

void printFunctionsList() {
    std::cout << "1)Удалить заданный элемент\n2)Печать всех элементов" << std::endl;
    std::cout << "3)Присвоение всем элементам предустановленных значений\n4)Выход" << std::endl;
}

bool deleteElement(Node*& head, const std::string& searchValue) {
    if (!head) return false;

    Node* current = head;
    do {
        if (current->fullName == searchValue) {
            if (current->next == current) { 
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