#include "Classes.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// 2. QUEUE - FIFO

void printQueue(queue<Book> q) {
    if (q.empty()) { cout << "Очередь пуста.\n"; return; }
    cout << "--- Очередь заказов (от первого к последнему) ---\n";
    int i = 1;
    while (!q.empty()) {
        cout << "[" << i++ << "] ";
        q.front().print();
        q.pop();
    }
}

void saveQueueToFile(queue<Book> q, const string& fn) {
    ofstream f(fn);
    if (!f) { cout << "Ошибка файла!\n"; return; }

    size_t count = q.size();
    f << count << "\n";

    while (!q.empty()) {
        q.front().save(f);
        q.pop();
    }
    cout << "Сохранено " << count << " книг в " << fn << "\n";
}

void loadQueueFromFile(queue<Book>& q, const string& fn) {
    ifstream f(fn);
    if (!f) { cout << "Файл не найден!\n"; return; }
    while (!q.empty()) q.pop();
    size_t n; f >> n; f.ignore(10000, '\n');
    for (size_t i = 0; i < n; ++i) {
        Book b; b.load(f); q.push(b);
    }
    cout << "Загружено " << n << " книг.\n";
}

void removeFromQueue(queue<Book>& q, const string& isbn) {
    queue<Book> temp;
    bool found = false;
    while (!q.empty()) {
        Book b = q.front(); q.pop();
        if (!found && b.getISBN() == isbn) { found = true; continue; }
        temp.push(b);
    }
    q = temp;
    if (found) cout << "Книга удалена.\n"; else cout << "Не найдена.\n";
}

void editInQueue(queue<Book>& q, const string& isbn) {
    queue<Book> temp;
    bool found = false;
    while (!q.empty()) {
        Book b = q.front(); q.pop();
        if (!found && b.getISBN() == isbn) {
            cout << "Введите новые данные:\n"; b.input(); found = true;
        }
        temp.push(b);
    }
    q = temp;
    if (found) cout << "Отредактировано.\n"; else cout << "Не найдена.\n";
}

void filterQueueByGenre(queue<Book> q, const string& genre) {
    bool any = false;
    while (!q.empty()) {
        if (q.front().getGenre() == genre) { q.front().print(); any = true; }
        q.pop();
    }
    if (!any) cout << "Книг жанра \"" << genre << "\" не найдено.\n";
}

void sortQueueByPrice(queue<Book>& q) {
    vector<Book> v;
    while (!q.empty()) { v.push_back(q.front()); q.pop(); }
    sort(v.begin(), v.end(), [](const Book& a, const Book& b) { return a.getPrice() > b.getPrice(); });
    for (const auto& b : v) q.push(b);
    cout << "Очередь отсортирована по убыванию цены.\n";
}

void demoQueue() {
    queue<Book> q;
    int choice;
    do {
        cout << "\n--- МЕНЮ QUEUE (Очередь заказов - FIFO) ---\n"
            << "1. Добавить заказ (push)\n"
            << "2. Удалить по ISBN\n"
            << "3. Редактировать по ISBN\n"
            << "4. Показать все\n"
            << "5. Поиск по ISBN\n"
            << "6. Сохранить в файл\n"
            << "7. Загрузить из файла\n"
            << "8. Фильтр по жанру\n"
            << "9. Сортировать по цене\n"
            << "0. Назад\n"
            << "Выбор: ";
        cin >> choice; cin.ignore(10000, '\n');

        switch (choice) {
        case 1: { Book b; b.input(); q.push(b); cout << "Заказ добавлен. Размер очереди: " << q.size() << "\n"; break; }
        case 2: { if (q.empty()) { cout << "Очередь пуста!\n"; break; } string isbn; cout << "ISBN: "; getline(cin, isbn); removeFromQueue(q, isbn); break; }
        case 3: { if (q.empty()) { cout << "Очередь пуста!\n"; break; } string isbn; cout << "ISBN: "; getline(cin, isbn); editInQueue(q, isbn); break; }
        case 4: printQueue(q); break;
        case 5: {
            if (q.empty()) { cout << "Очередь пуста!\n"; break; }
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            queue<Book> copy = q; bool ok = false;
            while (!copy.empty()) {
                if (copy.front().getISBN() == isbn) { copy.front().print(); ok = true; break; }
                copy.pop();
            }
            if (!ok) cout << "Не найдена.\n"; break;
        }
        case 6: saveQueueToFile(q, "queue_books.txt"); break;
        case 7: loadQueueFromFile(q, "queue_books.txt"); break;
        case 8: { if (q.empty()) { cout << "Очередь пуста!\n"; break; } string g; cout << "Жанр для фильтра: "; getline(cin, g); filterQueueByGenre(q, g); break; }
        case 9: { if (q.empty()) { cout << "Очередь пуста!\n"; break; } sortQueueByPrice(q); cout << "Результат:\n"; printQueue(q); break; }
        case 0: break;
        default: cout << "Неверный ввод!\n";
        }
    } while (choice != 0);
}
