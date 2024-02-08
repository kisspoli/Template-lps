/*Киселева Полина 9 группа
Реализовать шаблон класса двусвязный (двунаправленный) список DoublyLinked List<X>, хранящий элементы произвольного типа.
Класс должен содержать методы, перечисленные в варианте 1C.*/
#include "DoublyLinkedList.h"
#include "Double1.h"
#include "Menu.h"
#include <Windows.h>

void MainMenu();

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	MainMenu();
	return 0;
}

void MainMenu() {
	char menu;
	do {
		std::cout << "\nВыберите тип данных: " <<
			"\n1. int\n" <<
			"2. string\n" <<
			"3. Double1\n" <<
			"Другой символ. Выход\n-> ";
		if (!(std::cin >> menu)) {
			std::cin.clear();
			std::cin.ignore(1024, '\n');
		}
		std::cin.ignore(1024, '\n');
		switch (menu) {
		case '1': {
			DoublyLinkedList<int> list;
			ListMenu<int>(list);
			break;
		}
		case '2': {
			DoublyLinkedList<std::string> list;
			ListMenu<std::string>(list);
			break;
		}
		case '3': {
			DoublyLinkedList<Double1> list;
			ListMenu<Double1>(list);
			break;
		}
		default:
			break;
		}
	} while (menu >= '1' && menu <= '3');
}
