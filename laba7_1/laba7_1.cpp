#include <iostream>
#include "Node.h"
#include <Windows.h>
#include <regex>

using namespace std;

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Node* head = nullptr;

	if (!loadListFromFile(head, "list.txt")) {
		cerr << "Ошибка при чтении данных" << endl;
		return 1;
	}
	else cout << "Данные загружены" << endl;

	string input;
	regex valid_input("[1-5]");
	do {
		do {
			printFunctionsList();
			getline(cin, input);
		} while (!regex_match(input, valid_input));
		cout << endl;
		if (input == "1") {
			string Name;
			cout << "Введите ФИО: ";
			getline(cin, Name);
			if (deleteElement(head, Name)) saveListToFile(head, "list.txt");
			else cerr << "Ошибка при удалении" << endl;
		}
		else if (input == "2") {
			printList(head);
		}
		else if (input == "3") {
			setDefaultValues(head, constants::fullName, constants::age, constants::status);
			saveListToFile(head, "list.txt");
		}
		else if (input == "4") {
			setList(head, "list.txt");
		}
	} while (input != "5");
	clearList(head);
	cout << "До свидания!" << endl;
	return 0;
}
