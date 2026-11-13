#include <iostream>
#include "ContainerDemo.h"

using namespace std;

int main() {
    system("chcp 1251 > nul");
    system("cls");

    int choice;
    do {
        cout << "\n1. STACK (Склад книг - LIFO)\n"
            << "2. QUEUE (Очередь заказов - FIFO)\n"
            << "3. PRIORITY_QUEUE (Приоритет по цене)\n"
            << "0. Выход\n"
            << "Выбор: ";
        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice) {
        case 1: demoStack(); break;
        case 2: demoQueue(); break;
        case 3: demoPriorityQueue(); break;
        case 0: cout << "Выход...\n"; break;
        default: cout << "Неверный ввод!\n";
        }
    } while (choice != 0);

    return 0;
}