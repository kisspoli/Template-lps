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
    std::cout << "\n1. ������� ������ �� �����\n" << "2. ������� ������ � ����\n" <<
        "3. ������� ������ � �������\n" << "4. ������� ������ �� �������\n" <<
        "5. �������� ������� � ������ ������\n" << "6. �������� ������� � ����� ������\n" << "7. �������� ������\n" <<
        "8. ����� ������ �������� � ������\n" << "9. ����������, �������� �� ������ ������������\n" <<
        "10. ���������� ���������� ���������� �������� � ������\n" << "11. ����������� ������\n" <<
        "������ �����. �����\n--> ";
        while (!(std::cin >> menu)) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
        }
        std::cin.ignore(1024, '\n');
        switch (menu) {
        case 1: {
            std::string file_name;
            std::cout << "������� ��� �����: ";
            std::cin >> file_name;
            std::ifstream in(file_name);
            if (in) {
                try {
                    list.Read(in);
                }
                catch (std::exception) {
                    std::cerr << "������������ ������ � �����.\n";
                }
            }
            else
                std::cout << "���� �� ������.\n";
            break;
        }
        case 2: {
            std::string file_name;
            std::cout << "������� ��� �����: ";
            std::cin >> file_name;
            std::ofstream out(file_name);
            if (out) {
                try {
                    Print(out, list);
                }
                catch (std::exception) {
                    std::cerr << "�� ������� �������� ������ � ����.\n";
                }
            }
            else
                std::cout << "���� �� ������.\n";
            break;
        }
        case 3:
            std::cout << "������� ������: ";
            try {
                list.Read(std::cin);
            }
            catch (std::exception) {
                std::cerr << "������������ ������ � �����.\n";
            }
            break;
        case 4:
            Print(std::cout, list);
            break;
        case 5: {
            std::cout << "������� �������: ";
            try {
                std::string input;
                std::getline(std::cin, input);
                std::stringstream ss(input);
                X value;
                ss >> value;
                list.AddToBegin(value);
            }
            catch (std::exception) {
                std::cerr << "������������ ������ � �����.\n";
            }
            break;
        }
        case 6: {
            std::cout << "������� �������: ";
            try {
                std::string input;
                std::getline(std::cin, input);
                std::stringstream ss(input);
                X value;
                ss >> value;
                list.AddToEnd(value);
            }
            catch (std::exception) {
                std::cerr << "������������ ������ � �����.\n";
            }
            break;
        }
        case 7:
            list.Clear();
            break;
        case 8: {
            std::cout << "������� �������: ";
            try {
                std::string input;
                std::getline(std::cin, input);
                std::stringstream ss(input);
                X value;
                ss >> value;
                int index = list.FindIndex(value);
                if (index == -1)
                    std::cout << "������ �������� ���.\n";
                else
                    std::cout << "������ ��������: " << index << '\n';
            }
            catch (std::exception) {
                std::cerr << "������������ ������ � �����.\n";
            }
            break;
        }
        case 9:
            if(list.IsSymmetric())
                std::cout << "������ �����������.\n";
            else
                std::cout << "������ �� �����������.\n";
            break;
        case 10: {
            int unique = list.UniqueValuesCount();
            std::cout << "���������� �������� � ������: " << unique << '\n';
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
        stream << "������ ����\n";
    else
        list.Print(stream);
}