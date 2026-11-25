#include "Classes.h"
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
