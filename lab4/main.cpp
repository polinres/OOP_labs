#include <iostream>
#include "AssociativeDemo.h"

using namespace std;

int main() {
    system("chcp 1251 > nul");
    system("cls");

    int choice;
    do {
        cout << "\n1. MAP (ISBN -> Book, уникальные, сортировка)\n"
            << "2. SET (уникальные книги, сортировка)\n"
            << "3. MULTIMAP (Автор -> Book, дубликаты ключей)\n"
            << "4. MULTISET (книги, дубликаты элементов)\n"
            << "5. UNORDERED_MAP (ISBN -> Book, хеш)\n"
            << "6. UNORDERED_SET (уникальные книги, хеш)\n"
            << "7. UNORDERED_MULTIMAP (Автор -> Book, хеш + дубликаты)\n"
            << "8. UNORDERED_MULTISET (хеш + дубликаты)\n"
            << "0. Выход\n"
            << "Выбор: ";
        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice) {
        case 1: demoMap(); break;
        case 2: demoSet(); break;
        case 3: demoMultiMap(); break;
        case 4: demoMultiSet(); break;
        case 5: demoUnorderedMap(); break;
        case 6: demoUnorderedSet(); break;
        case 7: demoUnorderedMultiMap(); break;
        case 8: demoUnorderedMultiSet(); break;
        case 0: cout << "Выход...\n"; break;
        default: cout << "Неверный ввод!\n";
        }
    } while (choice != 0);

    return 0;
}