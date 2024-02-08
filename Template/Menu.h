#pragma once
#include <iostream>
#include "DoublyLinkedList.h"

template <typename X>
void ListMenu(DoublyLinkedList<X> list);

template <typename X>
void Print(std::ostream& stream, const DoublyLinkedList<X>& list);

template <typename X>
void ListMenu(DoublyLinkedList<X> list) {
    int menu;
    do {
    std::cout << "\n1. Считать список из файла\n" << "2. Вывести список в файл\n" <<
        "3. Считать список с консоли\n" << "4. Вывести список на консоль\n" <<
        "5. Добавить элемент в начало списка\n" << "6. Добавить элемент в конец списка\n" << "7. Очистить список\n" <<
        "8. Найти индекс значения в списке\n" << "9. Определить, является ли список симметричным\n" <<
        "10. Определить количество уникальных значений в списке\n" << "11. Перевернуть список\n" <<
        "Другое число. Назад\n--> ";
        while (!(std::cin >> menu)) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
        }
        std::cin.ignore(1024, '\n');
        switch (menu) {
        case 1: {
            std::string file_name;
            std::cout << "Введите имя файла: ";
            std::cin >> file_name;
            std::ifstream in(file_name);
            if (in) {
                try {
                    list.Read(in);
                }
                catch (std::exception) {
                    std::cerr << "Некорректные данные в файле.\n";
                }
            }
            else
                std::cout << "Файл не найден.\n";
            break;
        }
        case 2: {
            std::string file_name;
            std::cout << "Введите имя файла: ";
            std::cin >> file_name;
            std::ofstream out(file_name);
            if (out) {
                try {
                    Print(out, list);
                }
                catch (std::exception) {
                    std::cerr << "Не удалось записать данные в файл.\n";
                }
            }
            else
                std::cout << "Файл не найден.\n";
            break;
        }
        case 3:
            std::cout << "Вводите список: ";
            try {
                list.Read(std::cin);
            }
            catch (std::exception) {
                std::cerr << "Некорректные данные в вводе.\n";
            }
            break;
        case 4:
            Print(std::cout, list);
            break;
        case 5: {
            std::cout << "Введите элемент: ";
            try {
                std::string input;
                std::getline(std::cin, input);
                std::stringstream ss(input);
                X value;
                ss >> value;
                list.AddToBegin(value);
            }
            catch (std::exception) {
                std::cerr << "Некорректные данные в вводе.\n";
            }
            break;
        }
        case 6: {
            std::cout << "Введите элемент: ";
            try {
                std::string input;
                std::getline(std::cin, input);
                std::stringstream ss(input);
                X value;
                ss >> value;
                list.AddToEnd(value);
            }
            catch (std::exception) {
                std::cerr << "Некорректные данные в вводе.\n";
            }
            break;
        }
        case 7:
            list.Clear();
            break;
        case 8: {
            std::cout << "Введите элемент: ";
            try {
                std::string input;
                std::getline(std::cin, input);
                std::stringstream ss(input);
                X value;
                ss >> value;
                int index = list.FindIndex(value);
                if (index == -1)
                    std::cout << "Такого элемента нет.\n";
                else
                    std::cout << "Индекс элемента: " << index << '\n';
            }
            catch (std::exception) {
                std::cerr << "Некорректные данные в вводе.\n";
            }
            break;
        }
        case 9:
            if(list.IsSymmetric())
                std::cout << "Список симметричен.\n";
            else
                std::cout << "Список не симметричен.\n";
            break;
        case 10: {
            int unique = list.UniqueValuesCount();
            std::cout << "Уникальных значений в списке: " << unique << '\n';
            break;
        }
        case 11:
            list.Reverse();
            break;
        default:
            break;
        }
    } while (menu >= 1 && menu <= 12);
}

template <typename X>
void Print(std::ostream& stream, const DoublyLinkedList<X>& list) {
    if (list.getSize() == 0)
        stream << "Список пуст\n";
    else
        list.Print(stream);
}