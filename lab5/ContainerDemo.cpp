#include "ContainerDemo.h"
#include "Models.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// 1. STACK - LIFO

void printStack(stack<Book> s) {
    if (s.empty()) { cout << "Стек пуст.\n"; return; }
    cout << "--- Книги на складе (сверху вниз) ---\n";
    int i = 1;
    while (!s.empty()) {
        cout << "[" << i++ << "] ";
        s.top().print();
        s.pop();
    }
}

void saveStackToFile(stack<Book> s, const string& fn) {
    ofstream f(fn);
    if (!f) { cout << "Ошибка файла!\n"; return; }

    size_t count = s.size();
    f << count << "\n";

    while (!s.empty()) {
        s.top().save(f);
        s.pop();
    }
    cout << "Сохранено " << count << " книг в " << fn << "\n";
}

void loadStackFromFile(stack<Book>& s, const string& fn) {
    ifstream f(fn);
    if (!f) { cout << "Файл не найден!\n"; return; }
    while (!s.empty()) s.pop();
    size_t n; f >> n; f.ignore(10000, '\n');
    vector<Book> v(n);
    for (size_t i = 0; i < n; ++i) v[i].load(f);

    for (size_t i = n; i > 0; --i) s.push(v[i - 1]);
    cout << "Загружено " << n << " книг.\n";
}

void removeFromStack(stack<Book>& s, const string& isbn) {
    stack<Book> temp;
    bool found = false;
    while (!s.empty()) {
        Book b = s.top();
        s.pop();
        if (!found && b.getISBN() == isbn) { found = true; continue; }
        temp.push(b);
    }
    while (!temp.empty()) { s.push(temp.top()); temp.pop(); }
    if (found) cout << "Книга удалена.\n"; else cout << "Не найдена.\n";
}

void editInStack(stack<Book>& s, const string& isbn) {
    stack<Book> temp;
    bool found = false;
    while (!s.empty()) {
        Book b = s.top();
        s.pop();
        if (!found && b.getISBN() == isbn) {
            cout << "Введите новые данные:\n";
            b.input();
            found = true;
        }
        temp.push(b);
    }
    while (!temp.empty()) { s.push(temp.top()); temp.pop(); }
    if (found) cout << "Отредактировано.\n"; else cout << "Не найдена.\n";
}

void filterStackByGenre(stack<Book> s, const string& genre) {
    bool any = false;
    while (!s.empty()) {
        if (s.top().getGenre() == genre) { s.top().print(); any = true; }
        s.pop();
    }
    if (!any) cout << "Книг жанра \"" << genre << "\" не найдено.\n";
}

void sortStackByPrice(stack<Book>& s) {
    vector<Book> v;
    while (!s.empty()) { v.push_back(s.top()); s.pop(); }
    sort(v.begin(), v.end(), [](const Book& a, const Book& b) { return a.getPrice() > b.getPrice(); });
    for (size_t i = v.size(); i > 0; --i) s.push(v[i - 1]); // Возвращаем в стек
    cout << "Стек отсортирован по убыванию цены.\n";
}

void demoStack() {
    stack<Book> st;
    int choice;
    do {
        cout << "\n--- МЕНЮ STACK (Книги на складе - LIFO) ---\n"
            << "1. Добавить книгу (push)\n"
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
        case 1: { Book b; b.input(); st.push(b); cout << "Книга добавлена. Размер стека: " << st.size() << "\n"; break; }
        case 2: { if (st.empty()) { cout << "Стек пуст!\n"; break; } string isbn; cout << "ISBN: "; getline(cin, isbn); removeFromStack(st, isbn); break; }
        case 3: { if (st.empty()) { cout << "Стек пуст!\n"; break; } string isbn; cout << "ISBN: "; getline(cin, isbn); editInStack(st, isbn); break; }
        case 4: printStack(st); break;
        case 5: {
            if (st.empty()) { cout << "Стек пуст!\n"; break; }
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            stack<Book> copy = st; bool ok = false;
            while (!copy.empty()) {
                if (copy.top().getISBN() == isbn) { copy.top().print(); ok = true; break; }
                copy.pop();
            }
            if (!ok) cout << "Не найдена.\n"; break;
        }
        case 6: saveStackToFile(st, "stack_books.txt"); break;
        case 7: loadStackFromFile(st, "stack_books.txt"); break;
        case 8: { if (st.empty()) { cout << "Стек пуст!\n"; break; } string g; cout << "Жанр для фильтра: "; getline(cin, g); filterStackByGenre(st, g); break; }
        case 9: { if (st.empty()) { cout << "Стек пуст!\n"; break; } sortStackByPrice(st); cout << "Результат:\n"; printStack(st); break; }
        case 0: break;
        default: cout << "Неверный ввод!\n";
        }
    } while (choice != 0);
}

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
        case 6: { if (pq.empty()) { 
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