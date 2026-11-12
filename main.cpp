#include <iostream>
#include "ContainerDemo.h"

using namespace std;

int main() {
    system("chcp 1251 > nul");
    system("cls");

    int choice;
    do {
        cout << "\n1. Vector — каталог книг издательства\n"
            << "2. List — журналы (подписка)\n"
            << "3. Array — полка бестселлеров (фикс. 5 книг)\n"
            << "0. Выход\n"
            << "Выбор: ";
        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice) {
        case 1: demoVector(); break;
        case 2: demoList(); break;
        case 3: demoArray(); break;
        case 0: cout << "Выход из программы...\n"; break;
        default: cout << "Неверный ввод!\n";
        }
    } while (choice != 0);

    return 0;
}