#include <iostream>
#include "Node.h"
#include <Windows.h>
#include <regex>

using namespace std;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Node* head = nullptr;

	string fileName = constants::fileName;
	if (argc == 2) fileName = argv[1];
	else if (argc > 2) {
		cerr << "Ошибка: Некрректные аргументы" << endl;
		return 1;
	}

	if (!loadListFromFile(head, fileName)) {
		cerr << "Ошибка при чтении данных" << endl;
		return 1;
	}
	else cout << "Данные загружены" << endl;

	string input;
	regex valid_input("[1-4]");
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
			if (deleteElement(head, Name)) saveListToFile(head, fileName);
			else cerr << "Ошибка при удалении" << endl;
		}
		else if (input == "2") printList(head);
		else if (input == "3") {
			setDefaultValues(head, constants::fullName, constants::age, constants::status);
			saveListToFile(head, fileName);
		}
	} while (input != "4");
	clearList(head);
	cout << "До свидания!" << endl;
	return 0;
}
