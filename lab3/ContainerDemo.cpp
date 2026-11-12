#include "ContainerDemo.h"
#include "Models.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <array>

using namespace std;

// vector - книги
void vectorMenu() {
    cout << "\n--- МЕНЮ VECTOR (каталог книг издательства) ---\n"
        << "1. Добавить книгу\n"
        << "2. Удалить по ISBN\n"
        << "3. Редактировать по ISBN\n"
        << "4. Показать все\n"
        << "5. Поиск по ISBN\n"
        << "6. Сортировать по цене (убывание)\n"
        << "7. Сохранить в файл\n"
        << "8. Загрузить из файла\n"
        << "0. Назад\n"
        << "Выбор: ";
}

void demoVector() {
    PublishingHouse ph("Издательство 'Polly'");
    auto& vec = ph.books;

    int choice;
    do {
        vectorMenu();
        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice) {
        case 1: {
            Book b;
            cout << "Введите данные книги:\n";
            b.input();
            vec.push_back(b);
            cout << "Книга добавлена. Всего в каталоге: " << vec.size() << "\n";
            break;
        }
        case 2: {
            if (vec.empty()) { cout << "Каталог пуст!\n"; break; }
            string isbn; cout << "ISBN для удаления: "; getline(cin, isbn);
            auto it = find_if(vec.begin(), vec.end(),
                [&isbn](const Book& b) { return b.getISBN() == isbn; });
            if (it != vec.end()) { vec.erase(it); cout << "Удалена.\n"; }
            else cout << "Не найдена.\n";
            break;
        }
        case 3: {
            if (vec.empty()) { cout << "Каталог пуст!\n"; break; }
            string isbn; cout << "ISBN для редактирования: "; getline(cin, isbn);
            auto it = find_if(vec.begin(), vec.end(),
                [&isbn](const Book& b) { return b.getISBN() == isbn; });
            if (it != vec.end()) { cout << "Новые данные:\n"; it->input(); cout << "Готово.\n"; }
            else cout << "Не найдена.\n";
            break;
        }
        case 4: {
            if (vec.empty()) { cout << "Каталог пуст!\n"; break; }
            cout << "Издательство: " << ph.name << ", книг: " << vec.size() << "\n";
            for (const auto& b : vec) b.print();
            break;
        }
        case 5: {
            string isbn; cout << "ISBN для поиска: "; getline(cin, isbn);
            auto it = find_if(vec.begin(), vec.end(),
                [&isbn](const Book& b) { return b.getISBN() == isbn; });
            if (it != vec.end()) it->print();
            else cout << "Не найдена.\n";
            break;
        }
        case 6: {
            sort(vec.begin(), vec.end());
            cout << "Отсортировано по убыванию цены:\n";
            for (const auto& b : vec) b.print();
            break;
        }
        case 7: {
            ofstream f("vector_books.txt");
            if (!f) { cout << "Ошибка файла!\n"; break; }
            f << vec.size() << "\n";
            for (const auto& b : vec) b.save(f);
            f.close();
            cout << "Сохранено в vector_books.txt\n";
            break;
        }
        case 8: {
            ifstream f("vector_books.txt");
            if (!f) { cout << "Файл не найден!\n"; break; }
            size_t n; f >> n; f.ignore(10000, '\n');
            vec.clear();
            for (size_t i = 0; i < n; ++i) { Book b; b.load(f); vec.push_back(b); }
            f.close();
            cout << "Загружено " << n << " книг.\n";
            break;
        }
        case 0: break;
        default: cout << "Неверный ввод.\n";
        }
    } while (choice != 0);
}

// list - журналы
void listMenu() {
    cout << "\n--- МЕНЮ LIST (журналы издательства) ---\n"
        << "1. Добавить журнал в конец\n"
        << "2. Добавить новый выпуск в начало (push_front)\n"
        << "3. Удалить по названию\n"
        << "4. Редактировать по названию\n"
        << "5. Показать все\n"
        << "6. Поиск по названию\n"
        << "7. Сортировать по номеру выпуска\n"
        << "8. Сохранить в файл\n"
        << "9. Загрузить из файла\n"
        << "0. Назад\n"
        << "Выбор: ";
}

void demoList() {
    list<Magazine> lst;
    int choice;

    do {
        listMenu();
        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice) {
        case 1: {
            Magazine m;
            cout << "Введите данные журнала:\n";
            m.input();
            lst.push_back(m);
            cout << "Журнал добавлен в конец. Всего: " << lst.size() << "\n";
            break;
        }
        case 2: {
            Magazine m;
            cout << "Введите данные нового выпуска:\n";
            m.input();
            lst.push_front(m);
            cout << "Выпуск добавлен в начало. Всего: " << lst.size() << "\n";
            break;
        }
        case 3: {
            if (lst.empty()) { cout << "Список пуст!\n"; break; }
            string title; cout << "Название для удаления: "; getline(cin, title);
            auto it = find_if(lst.begin(), lst.end(),
                [&title](const Magazine& m) { return m.getTitle() == title; });
            if (it != lst.end()) { lst.erase(it); cout << "Удалён.\n"; }
            else cout << "Не найден.\n";
            break;
        }
        case 4: {
            if (lst.empty()) { cout << "Список пуст!\n"; break; }
            string title; cout << "Название для редактирования: "; getline(cin, title);
            auto it = find_if(lst.begin(), lst.end(),
                [&title](const Magazine& m) { return m.getTitle() == title; });
            if (it != lst.end()) {
                cout << "Новые данные:\n";
                Magazine tmp; tmp.input();
                *it = tmp;
                cout << "Готово.\n";
            }
            else cout << "Не найден.\n";
            break;
        }
        case 5: {
            if (lst.empty()) { cout << "Список пуст!\n"; break; }
            for (const auto& m : lst) m.print();
            break;
        }
        case 6: {
            string title; cout << "Название для поиска: "; getline(cin, title);
            auto it = find_if(lst.begin(), lst.end(),
                [&title](const Magazine& m) { return m.getTitle() == title; });
            if (it != lst.end()) it->print();
            else cout << "Не найден.\n";
            break;
        }
        case 7: {
            lst.sort([](const Magazine& a, const Magazine& b) {
                return a.getIssue() < b.getIssue();
                });
            cout << "Отсортировано по номеру выпуска:\n";
            for (const auto& m : lst) m.print();
            break;
        }
        case 8: {
            ofstream f("list_magazines.txt");
            if (!f) { cout << "Ошибка файла!\n"; break; }
            f << lst.size() << "\n";
            for (const auto& m : lst) m.save(f);
            f.close();
            cout << "Сохранено в list_magazines.txt\n";
            break;
        }
        case 9: {
            ifstream f("list_magazines.txt");
            if (!f) { cout << "Файл не найден!\n"; break; }
            size_t n; f >> n; f.ignore(10000, '\n');
            lst.clear();
            for (size_t i = 0; i < n; ++i) { Magazine m; m.load(f); lst.push_back(m); }
            f.close();
            cout << "Загружено " << n << " журналов.\n";
            break;
        }
        case 0: break;
        default: cout << "Неверный ввод.\n";
        }
    } while (choice != 0);
}

// array - бестселлеры(топ5)
const size_t MAX_ARR = 5;

void arrayMenu() {
    cout << "\n--- МЕНЮ ARRAY (полка бестселлеров, размер " << MAX_ARR << ") ---\n"
        << "1. Добавить книгу на полку\n"
        << "2. Удалить по ISBN (со сдвигом)\n"
        << "3. Редактировать по ISBN\n"
        << "4. Показать все\n"
        << "5. Поиск по ISBN\n"
        << "6. Сортировать по цене\n"
        << "7. Сохранить в файл\n"
        << "8. Загрузить из файла\n"
        << "0. Назад\n"
        << "Выбор: ";
}

void demoArray() {
    array<Book, MAX_ARR> arr;
    size_t used = 0;
    int choice;

    do {
        arrayMenu();
        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice) {
        case 1: {
            if (used >= MAX_ARR) { cout << "Полка заполнена (" << MAX_ARR << ")!\n"; break; }
            Book b;
            cout << "Введите данные книги:\n";
            b.input();
            arr[used] = b;
            ++used;
            cout << "Занято: " << used << "/" << MAX_ARR << "\n";
            break;
        }
        case 2: {
            if (used == 0) { cout << "Полка пуста!\n"; break; }
            string isbn; cout << "ISBN для удаления: "; getline(cin, isbn);
            size_t idx = used;
            for (size_t i = 0; i < used; ++i)
                if (arr[i].getISBN() == isbn) { idx = i; break; }
            if (idx == used) { cout << "Не найдена.\n"; break; }
            for (size_t i = idx; i + 1 < used; ++i) arr[i] = arr[i + 1];
            --used;
            cout << "Удалена. Занято: " << used << "/" << MAX_ARR << "\n";
            break;
        }
        case 3: {
            if (used == 0) { cout << "Полка пуста!\n"; break; }
            string isbn; cout << "ISBN для редактирования: "; getline(cin, isbn);
            size_t idx = used;
            for (size_t i = 0; i < used; ++i)
                if (arr[i].getISBN() == isbn) { idx = i; break; }
            if (idx == used) { cout << "Не найдена.\n"; break; }
            cout << "Новые данные:\n";
            arr[idx].input();
            cout << "Готово.\n";
            break;
        }
        case 4: {
            if (used == 0) { cout << "Полка пуста!\n"; break; }
            for (size_t i = 0; i < used; ++i) arr[i].print();
            break;
        }
        case 5: {
            string isbn; cout << "ISBN для поиска: "; getline(cin, isbn);
            bool ok = false;
            for (size_t i = 0; i < used; ++i)
                if (arr[i].getISBN() == isbn) { arr[i].print(); ok = true; break; }
            if (!ok) cout << "Не найдена.\n";
            break;
        }
        case 6: {
            sort(arr.begin(), arr.begin() + used);
            cout << "Отсортировано по цене (убывание):\n";
            for (size_t i = 0; i < used; ++i) arr[i].print();
            break;
        }
        case 7: {
            ofstream f("array_top_books.txt");
            if (!f) { cout << "Ошибка файла!\n"; break; }
            f << used << "\n";
            for (size_t i = 0; i < used; ++i) arr[i].save(f);
            f.close();
            cout << "Сохранено в array_top_books.txt\n";
            break;
        }
        case 8: {
            ifstream f("array_top_books.txt");
            if (!f) { cout << "Файл не найден!\n"; break; }
            size_t n; f >> n; f.ignore(10000, '\n');
            if (n > MAX_ARR) { n = MAX_ARR; cout << "(обрезано до " << MAX_ARR << ")\n"; }
            used = n;
            for (size_t i = 0; i < used; ++i) arr[i].load(f);
            f.close();
            cout << "Загружено " << used << " книг.\n";
            break;
        }
        case 0: break;
        default: cout << "Неверный ввод.\n";
        }
    } while (choice != 0);
}