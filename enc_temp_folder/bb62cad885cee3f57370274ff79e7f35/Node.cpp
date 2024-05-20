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

void saveListToFile(Node* head, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Ошибка открытия файла для записи" << std::endl;
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
    std::cout << "3)Присвоение всем элементам предустановленных значений" << std::endl;
    std::cout << "4)Обновить данные (получить с файла)\n5)Выход" << std::endl;
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
            std::cout << "Успешно удалено" << std::endl;
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
    addElement(head, "Ольга Петрова", 35, "Не замужем");
    addElement(head, "Михаил Иванов", 42, "Женат");
    addElement(head, "Екатерина Сидорова", 28, "Не замужем");
    addElement(head, "Александр Кузнецов", 39, "Женат");
    addElement(head, "Мария Романова", 31, "Не замужем");
    addElement(head, "Дмитрий Смирнов", 27, "Не женат");
    addElement(head, "Анна Лебедева", 24, "Не замужем");
    addElement(head, "Сергей Попов", 45, "Женат");
    addElement(head, "Елена Соколова", 33, "Не замужем");
    addElement(head, "Иван Орлов", 29, "Не женат");
    saveListToFile(head, filename);
}
