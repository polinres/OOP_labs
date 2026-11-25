#include "Classes.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// 3. PRIORITY_QUEUE

void printPQ(priority_queue<Book> pq) {
    if (pq.empty()) { cout << "Очередь пуста.\n"; return; }
    cout << "--- Книги по убыванию цены (приоритета) ---\n";
    int i = 1;
    while (!pq.empty()) {
        cout << "[" << i++ << "] ";
        pq.top().print();
        pq.pop();
    }
}

void savePQToFile(priority_queue<Book> pq, const string& fn) {
    ofstream f(fn);
    if (!f) { cout << "Ошибка файла!\n"; return; }

    size_t count = pq.size();
    f << count << "\n";

    while (!pq.empty()) {
        pq.top().save(f);
        pq.pop();
    }
    cout << "Сохранено " << count << " книг в " << fn << "\n";
}

void loadPQFromFile(priority_queue<Book>& pq, const string& fn) {
    ifstream f(fn);
    if (!f) { cout << "Файл не найден!\n"; return; }
    while (!pq.empty()) pq.pop();
    size_t n; f >> n; f.ignore(10000, '\n');
    for (size_t i = 0; i < n; ++i) {
        Book b; b.load(f); pq.push(b);
    }
    cout << "Загружено " << n << " книг.\n";
}

void removeFromPQ(priority_queue<Book>& pq, const string& isbn) {
    priority_queue<Book> temp;
    bool found = false;
    while (!pq.empty()) {
        Book b = pq.top(); pq.pop();
        if (!found && b.getISBN() == isbn) { found = true; continue; }
        temp.push(b);
    }
    pq = temp;
    if (found) cout << "Книга удалена.\n"; else cout << "Не найдена.\n";
}

void editInPQ(priority_queue<Book>& pq, const string& isbn) {
    priority_queue<Book> temp;
    bool found = false;
    while (!pq.empty()) {
        Book b = pq.top(); pq.pop();
        if (!found && b.getISBN() == isbn) {
            cout << "Введите новые данные:\n"; b.input(); found = true;
        }
        temp.push(b);
    }
    pq = temp;
    if (found) cout << "Отредактировано.\n"; else cout << "Не найдена.\n";
}

void filterPQByGenre(priority_queue<Book> pq, const string& genre) {
    bool any = false;
    while (!pq.empty()) {
        if (pq.top().getGenre() == genre) { pq.top().print(); any = true; }
        pq.pop();
    }
    if (!any) cout << "Книг жанра \"" << genre << "\" не найдено.\n";
}

void demoPriorityQueue() {
    priority_queue<Book> pq;
    int choice;
    do {
        cout << "\n--- МЕНЮ PRIORITY_QUEUE (Приоритет по цене) ---\n"
            << "1. Добавить книгу (push)\n"
            << "2. Удалить по ISBN\n"
            << "3. Редактировать по ISBN\n"
            << "4. Показать все (от самой дорогой)\n"
            << "5. Поиск по ISBN\n"
            << "6. Фильтр по жанру\n"
            << "7. Сохранить в файл\n"
            << "8. Загрузить из файла\n"
            << "0. Назад\n"
            << "Выбор: ";
        cin >> choice; cin.ignore(10000, '\n');

        switch (choice) {
        case 1: { Book b; b.input(); pq.push(b); cout << "Книга добавлена. Размер: " << pq.size() << "\n"; break; }
        case 2: { if (pq.empty()) { cout << "Очередь пуста!\n"; break; } string isbn; cout << "ISBN: "; getline(cin, isbn); removeFromPQ(pq, isbn); break; }
        case 3: { if (pq.empty()) { cout << "Очередь пуста!\n"; break; } string isbn; cout << "ISBN: "; getline(cin, isbn); editInPQ(pq, isbn); break; }
        case 4: printPQ(pq); break;
        case 5: {
            if (pq.empty()) { cout << "Очередь пуста!\n"; break; }
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            priority_queue<Book> copy = pq; bool ok = false;
            while (!copy.empty()) {
                if (copy.top().getISBN() == isbn) { copy.top().print(); ok = true; break; }
                copy.pop();
            }
            if (!ok) cout << "Не найдена.\n"; break;
        }
        case 6: {
            if (pq.empty()) {
                cout << "Очередь пуста!\n"; break;
            } string g;
            cout << "Жанр для фильтра: "; getline(cin, g); filterPQByGenre(pq, g); break;
        }
        case 7: savePQToFile(pq, "pq_books.txt"); break;
        case 8: loadPQFromFile(pq, "pq_books.txt"); break;
        case 0: break;
        default: cout << "Неверный ввод!\n";
        }
    } while (choice != 0);
}