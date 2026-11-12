#include "AssociativeDemo.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Создание "пустой" книги только с ISBN — для поиска в set/multiset
static Book makeDummy(const string& isbn) {
    return Book("", 0, 0, 0.0, isbn, "", Author());
}

// Вывод книг (из set/multiset) отсортированных по цене
template <typename Iter>
static void printSortedByPrice(Iter begin, Iter end) {
    vector<Book> v;
    for (auto it = begin; it != end; ++it) v.push_back(*it);
    sort(v.begin(), v.end()); // использует Book::operator< (цена по убыванию)
    for (const auto& b : v) b.print();
}

// Вывод книг (из map/multimap) отсортированных по цене
template <typename Iter>
static void printMapSortedByPrice(Iter begin, Iter end) {
    vector<Book> v;
    for (auto it = begin; it != end; ++it) v.push_back(it->second);
    sort(v.begin(), v.end());
    for (const auto& b : v) b.print();
}

// 1. MAP (ключ = ISBN)
void demoMap() {
    map<string, Book> m;
    int choice;
    do {
        cout << "\n--- MAP (ISBN -> Book, уникальные ключи, сортировка по ISBN) ---\n"
            << "1. Добавить книгу\n"
            << "2. Удалить по ISBN\n"
            << "3. Редактировать по ISBN\n"
            << "4. Найти по ISBN\n"
            << "5. Показать все (по ISBN)\n"
            << "6. Показать по цене\n"
            << "7. Сохранить в файл\n"
            << "8. Загрузить из файла\n"
            << "0. Назад\n"
            << "Выбор: ";
        cin >> choice; cin.ignore(10000, '\n');

        switch (choice) {
        case 1: {
            Book b; b.input();
            m[b.getISBN()] = b;
            cout << "Добавлено. Всего: " << m.size() << "\n";
            break;
        }
        case 2: {
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            if (m.erase(isbn)) cout << "Удалена.\n";
            else cout << "Не найдена.\n";
            break;
        }
        case 3: {
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            auto it = m.find(isbn);
            if (it != m.end()) {
                cout << "Новые данные:\n";
                Book b; b.input();
                m.erase(it);
                m[b.getISBN()] = b;
            }
            else cout << "Не найдена.\n";
            break;
        }
        case 4: {
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            auto it = m.find(isbn);
            if (it != m.end()) it->second.print();
            else cout << "Не найдена.\n";
            break;
        }
        case 5: {
            if (m.empty()) { cout << "Пусто.\n"; break; }
            for (const auto& p : m) {
                cout << "ISBN: " << p.first << " -> ";
                p.second.print();
            }
            break;
        }
        case 6: {
            if (m.empty()) { cout << "Пусто.\n"; break; }
            printMapSortedByPrice(m.begin(), m.end());
            break;
        }
        case 7: {
            ofstream f("map_books.txt");
            if (!f) { cout << "Ошибка файла!\n"; break; }
            f << m.size() << "\n";
            for (const auto& p : m) p.second.save(f);
            f.close();
            cout << "Сохранено в map_books.txt\n";
            break;
        }
        case 8: {
            ifstream f("map_books.txt");
            if (!f) { cout << "Файл не найден!\n"; break; }
            size_t n; f >> n; f.ignore(10000, '\n');
            m.clear();
            for (size_t i = 0; i < n; ++i) {
                Book b; b.load(f);
                m[b.getISBN()] = b;
            }
            f.close();
            cout << "Загружено " << n << " книг.\n";
            break;
        }
        case 0: break;
        default: cout << "Неверный ввод.\n";
        }
    } while (choice != 0);
}

// 2. SET (уникальные книги, сортировка по ISBN)
void demoSet() {
    set<Book, BookByISBN> s;
    int choice;
    do {
        cout << "\n--- SET (уникальные книги, сортировка по ISBN) ---\n"
            << "1. Добавить книгу\n"
            << "2. Удалить по ISBN\n"
            << "3. Редактировать по ISBN\n"
            << "4. Найти по ISBN\n"
            << "5. Показать все (по ISBN)\n"
            << "6. Показать по цене\n"
            << "7. Сохранить в файл\n"
            << "8. Загрузить из файла\n"
            << "0. Назад\n"
            << "Выбор: ";
        cin >> choice; cin.ignore(10000, '\n');

        switch (choice) {
        case 1: {
            Book b; b.input();
            auto res = s.insert(b);
            if (res.second) cout << "Добавлено. Всего: " << s.size() << "\n";
            else cout << "Книга с таким ISBN уже есть!\n";
            break;
        }
        case 2: {
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            if (s.erase(makeDummy(isbn))) cout << "Удалена.\n";
            else cout << "Не найдена.\n";
            break;
        }
        case 3: {
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            auto it = s.find(makeDummy(isbn));
            if (it != s.end()) {
                cout << "Новые данные:\n";
                Book b; b.input();
                s.erase(it);
                s.insert(b);
            }
            else cout << "Не найдена.\n";
            break;
        }
        case 4: {
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            auto it = s.find(makeDummy(isbn));
            if (it != s.end()) it->print();
            else cout << "Не найдена.\n";
            break;
        }
        case 5: {
            if (s.empty()) { cout << "Пусто.\n"; break; }
            for (const auto& b : s) b.print();
            break;
        }
        case 6: {
            if (s.empty()) { cout << "Пусто.\n"; break; }
            printSortedByPrice(s.begin(), s.end());
            break;
        }
        case 7: {
            ofstream f("set_books.txt");
            f << s.size() << "\n";
            for (const auto& b : s) b.save(f);
            f.close();
            cout << "Сохранено в set_books.txt\n";
            break;
        }
        case 8: {
            ifstream f("set_books.txt");
            if (!f) { cout << "Файл не найден!\n"; break; }
            size_t n; f >> n; f.ignore(10000, '\n');
            s.clear();
            for (size_t i = 0; i < n; ++i) {
                Book b; b.load(f);
                s.insert(b);
            }
            f.close();
            cout << "Загружено.\n";
            break;
        }
        case 0: break;
        default: cout << "Неверный ввод.\n";
        }
    } while (choice != 0);
}

// 3. MULTIMAP (ключ = Автор, дубликаты разрешены) 
void demoMultiMap() {
    multimap<string, Book> mm;
    int choice;
    do {
        cout << "\n--- MULTIMAP (Автор -> Book, дубликаты ключей) ---\n"
            << "1. Добавить книгу\n"
            << "2. Удалить все книги автора\n"
            << "3. Редактировать книгу по ISBN\n"
            << "4. Найти книги автора\n"
            << "5. Показать все (по автору)\n"
            << "6. Показать по цене\n"
            << "7. Сохранить в файл\n"
            << "8. Загрузить из файла\n"
            << "0. Назад\n"
            << "Выбор: ";
        cin >> choice; cin.ignore(10000, '\n');

        switch (choice) {
        case 1: {
            Book b; b.input();
            mm.insert(make_pair(b.getAuthor().getName(), b));
            cout << "Добавлено. Всего: " << mm.size() << "\n";
            break;
        }
        case 2: {
            string name; cout << "ФИО автора: "; getline(cin, name);
            size_t n = mm.erase(name);
            cout << "Удалено книг: " << n << "\n";
            break;
        }
        case 3: {
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            bool found = false;
            for (auto it = mm.begin(); it != mm.end(); ++it) {
                if (it->second.getISBN() == isbn) {
                    cout << "Новые данные:\n";
                    Book b; b.input();
                    mm.erase(it);
                    mm.insert(make_pair(b.getAuthor().getName(), b));
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Не найдена.\n";
            break;
        }
        case 4: {
            string name; cout << "ФИО автора: "; getline(cin, name);
            auto range = mm.equal_range(name);
            if (range.first == range.second) cout << "Не найдено.\n";
            else for (auto it = range.first; it != range.second; ++it) it->second.print();
            break;
        }
        case 5: {
            if (mm.empty()) { cout << "Пусто.\n"; break; }
            for (const auto& p : mm) {
                cout << "Автор: " << p.first << " -> ";
                p.second.print();
            }
            break;
        }
        case 6: {
            if (mm.empty()) { cout << "Пусто.\n"; break; }
            printMapSortedByPrice(mm.begin(), mm.end());
            break;
        }
        case 7: {
            ofstream f("multimap_books.txt");
            f << mm.size() << "\n";
            for (const auto& p : mm) p.second.save(f);
            f.close();
            cout << "Сохранено в multimap_books.txt\n";
            break;
        }
        case 8: {
            ifstream f("multimap_books.txt");
            if (!f) { cout << "Файл не найден!\n"; break; }
            size_t n; f >> n; f.ignore(10000, '\n');
            mm.clear();
            for (size_t i = 0; i < n; ++i) {
                Book b; b.load(f);
                mm.insert(make_pair(b.getAuthor().getName(), b));
            }
            f.close();
            cout << "Загружено " << n << " книг.\n";
            break;
        }
        case 0: break;
        default: cout << "Неверный ввод.\n";
        }
    } while (choice != 0);
}

// 4. MULTISET (дубликаты разрешены)
void demoMultiSet() {
    multiset<Book, BookByISBN> ms;
    int choice;
    do {
        cout << "\n--- MULTISET (книги, дубликаты разрешены, сортировка по ISBN) ---\n"
            << "1. Добавить книгу\n"
            << "2. Удалить одну копию по ISBN\n"
            << "3. Удалить ВСЕ копии по ISBN\n"
            << "4. Редактировать по ISBN\n"
            << "5. Найти по ISBN\n"
            << "6. Показать все\n"
            << "7. Показать по цене\n"
            << "8. Сохранить в файл\n"
            << "9. Загрузить из файла\n"
            << "0. Назад\n"
            << "Выбор: ";
        cin >> choice; cin.ignore(10000, '\n');

        switch (choice) {
        case 1: {
            Book b; b.input();
            ms.insert(b);
            cout << "Добавлено. Всего: " << ms.size() << "\n";
            break;
        }
        case 2: {
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            auto it = ms.find(makeDummy(isbn));
            if (it != ms.end()) { ms.erase(it); cout << "Удалена одна копия.\n"; }
            else cout << "Не найдена.\n";
            break;
        }
        case 3: {
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            size_t n = ms.erase(makeDummy(isbn));
            cout << "Удалено копий: " << n << "\n";
            break;
        }
        case 4: {
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            auto it = ms.find(makeDummy(isbn));
            if (it != ms.end()) {
                cout << "Новые данные:\n";
                Book b; b.input();
                ms.erase(it);
                ms.insert(b);
            }
            else cout << "Не найдена.\n";
            break;
        }
        case 5: {
            string isbn; cout << "ISBN: "; getline(cin, isbn);
            auto it = ms.find(makeDummy(isbn));
            if (it != ms.end()) it->print();
            else cout << "Не найдена.\n";
            break;
        }
        case 6: {
            if (ms.empty()) { cout << "Пусто.\n"; break; }
            for (const auto& b : ms) b.print();
            break;
        }
        case 7: {
            if (ms.empty()) { cout << "Пусто.\n"; break; }
            printSortedByPrice(ms.begin(), ms.end());
            break;
        }
        case 8: {
            ofstream f("multiset_books.txt");
            f << ms.size() << "\n";
            for (const auto& b : ms) b.save(f);
            f.close();
            cout << "Сохранено.\n";
            break;
        }
        case 9: {
            ifstream f("multiset_books.txt");
            if (!f) { cout << "Файл не найден!\n"; break; }
            size_t n; f >> n; f.ignore(10000, '\n');
            ms.clear();
            for (size_t i = 0; i < n; ++i) {
                Book b; b.load(f);
                ms.insert(b);
            }
            f.close();
            cout << "Загружено.\n";
            break;
        }
        case 0: break;
        default: cout << "Неверный ввод.\n";
        }
    } while (choice != 0);
}

// 5. UNORDERED_MAP 
void demoUnorderedMap() {
    unordered_map<string, Book> um;
    int choice;
    do {
        cout << "\n--- UNORDERED_MAP (ISBN -> Book, хеш-таблица) ---\n"
            << "1. Добавить\n2. Удалить по ISBN\n3. Редактировать\n"
            << "4. Найти\n5. Показать все (без сортировки)\n6. Показать по цене\n"
            << "7. Сохранить\n8. Загрузить\n0. Назад\nВыбор: ";
        cin >> choice; cin.ignore(10000, '\n');

        switch (choice) {
        case 1: { Book b; b.input(); um[b.getISBN()] = b; break; }
        case 2: { string i; cout << "ISBN: "; getline(cin, i); um.erase(i) ? cout << "OK\n" : cout << "Нет\n"; break; }
        case 3: {
            string i; cout << "ISBN: "; getline(cin, i);
            auto it = um.find(i);
            if (it != um.end()) { Book b; b.input(); it->second = b; }
            else cout << "Нет.\n";
            break;
        }
        case 4: {
            string i; cout << "ISBN: "; getline(cin, i);
            auto it = um.find(i);
            if (it != um.end()) it->second.print(); else cout << "Нет.\n";
            break;
        }
        case 5: { for (const auto& p : um) { cout << "ISBN: " << p.first << " -> "; p.second.print(); } break; }
        case 6: { printMapSortedByPrice(um.begin(), um.end()); break; }
        case 7: {
            ofstream f("umap_books.txt"); f << um.size() << "\n";
            for (const auto& p : um) p.second.save(f);
            f.close(); cout << "OK\n"; break;
        }
        case 8: {
            ifstream f("umap_books.txt"); if (!f) { cout << "Нет файла\n"; break; }
            size_t n; f >> n; f.ignore(10000, '\n'); um.clear();
            for (size_t i = 0; i < n; ++i) { Book b; b.load(f); um[b.getISBN()] = b; }
            f.close(); cout << "OK\n"; break;
        }
        case 0: break;
        default: cout << "Неверный ввод.\n";
        }
    } while (choice != 0);
}

// 6. UNORDERED_SET 
void demoUnorderedSet() {
    unordered_set<Book, BookHash, BookEqual> us;
    int choice;
    do {
        cout << "\n--- UNORDERED_SET (уникальные книги, хеш) ---\n"
            << "1. Добавить\n2. Удалить по ISBN\n3. Редактировать\n"
            << "4. Найти\n5. Показать все\n6. Показать по цене\n"
            << "7. Сохранить\n8. Загрузить\n0. Назад\nВыбор: ";
        cin >> choice; cin.ignore(10000, '\n');

        switch (choice) {
        case 1: { Book b; b.input(); us.insert(b); break; }
        case 2: { string i; cout << "ISBN: "; getline(cin, i); us.erase(makeDummy(i)) ? cout << "OK\n" : cout << "Нет\n"; break; }
        case 3: {
            string i; cout << "ISBN: "; getline(cin, i);
            auto it = us.find(makeDummy(i));
            if (it != us.end()) { Book b; b.input(); us.erase(it); us.insert(b); }
            else cout << "Нет.\n";
            break;
        }
        case 4: {
            string i; cout << "ISBN: "; getline(cin, i);
            auto it = us.find(makeDummy(i));
            if (it != us.end()) it->print(); else cout << "Нет.\n";
            break;
        }
        case 5: { for (const auto& b : us) b.print(); break; }
        case 6: { printSortedByPrice(us.begin(), us.end()); break; }
        case 7: {
            ofstream f("uset_books.txt"); f << us.size() << "\n";
            for (const auto& b : us) b.save(f);
            f.close(); cout << "OK\n"; break;
        }
        case 8: {
            ifstream f("uset_books.txt"); if (!f) { cout << "Нет файла\n"; break; }
            size_t n; f >> n; f.ignore(10000, '\n'); us.clear();
            for (size_t i = 0; i < n; ++i) { Book b; b.load(f); us.insert(b); }
            f.close(); cout << "OK\n"; break;
        }
        case 0: break;
        default: cout << "Неверный ввод.\n";
        }
    } while (choice != 0);
}

// 7. UNORDERED_MULTIMAP
void demoUnorderedMultiMap() {
    unordered_multimap<string, Book> umm;
    int choice;
    do {
        cout << "\n--- UNORDERED_MULTIMAP (Автор -> Book, хеш, дубликаты) ---\n"
            << "1. Добавить\n2. Удалить все книги автора\n3. Редактировать по ISBN\n"
            << "4. Найти книги автора\n5. Показать все\n6. Показать по цене\n"
            << "7. Сохранить\n8. Загрузить\n0. Назад\nВыбор: ";
        cin >> choice; cin.ignore(10000, '\n');

        switch (choice) {
        case 1: { Book b; b.input(); umm.insert(make_pair(b.getAuthor().getName(), b)); break; }
        case 2: {
            string n; cout << "Автор: "; getline(cin, n);
            cout << "Удалено: " << umm.erase(n) << "\n"; break;
        }
        case 3: {
            string i; cout << "ISBN: "; getline(cin, i);
            for (auto it = umm.begin(); it != umm.end(); ++it)
                if (it->second.getISBN() == i) {
                    Book b; b.input(); umm.erase(it);
                    umm.insert(make_pair(b.getAuthor().getName(), b)); break;
                }
            break;
        }
        case 4: {
            string n; cout << "Автор: "; getline(cin, n);
            auto r = umm.equal_range(n);
            for (auto it = r.first; it != r.second; ++it) it->second.print();
            break;
        }
        case 5: { for (const auto& p : umm) { cout << p.first << " -> "; p.second.print(); } break; }
        case 6: { printMapSortedByPrice(umm.begin(), umm.end()); break; }
        case 7: {
            ofstream f("ummap_books.txt"); f << umm.size() << "\n";
            for (const auto& p : umm) p.second.save(f);
            f.close(); cout << "OK\n"; break;
        }
        case 8: {
            ifstream f("ummap_books.txt"); if (!f) { cout << "Нет файла\n"; break; }
            size_t n; f >> n; f.ignore(10000, '\n'); umm.clear();
            for (size_t i = 0; i < n; ++i) { Book b; b.load(f); umm.insert(make_pair(b.getAuthor().getName(), b)); }
            f.close(); cout << "OK\n"; break;
        }
        case 0: break;
        default: cout << "Неверный ввод.\n";
        }
    } while (choice != 0);
}

// 8. UNORDERED_MULTISET 
void demoUnorderedMultiSet() {
    unordered_multiset<Book, BookHash, BookEqual> ums;
    int choice;
    do {
        cout << "\n--- UNORDERED_MULTISET (хеш, дубликаты) ---\n"
            << "1. Добавить\n2. Удалить одну копию\n3. Удалить ВСЕ копии\n"
            << "4. Редактировать\n5. Найти\n6. Показать все\n7. Показать по цене\n"
            << "8. Сохранить\n9. Загрузить\n0. Назад\nВыбор: ";
        cin >> choice; cin.ignore(10000, '\n');

        switch (choice) {
        case 1: { Book b; b.input(); ums.insert(b); break; }
        case 2: {
            string i; cout << "ISBN: "; getline(cin, i);
            auto it = ums.find(makeDummy(i));
            if (it != ums.end()) ums.erase(it);
            break;
        }
        case 3: { string i; cout << "ISBN: "; getline(cin, i); cout << "Удалено: " << ums.erase(makeDummy(i)) << "\n"; break; }
        case 4: {
            string i; cout << "ISBN: "; getline(cin, i);
            auto it = ums.find(makeDummy(i));
            if (it != ums.end()) { Book b; b.input(); ums.erase(it); ums.insert(b); }
            break;
        }
        case 5: {
            string i; cout << "ISBN: "; getline(cin, i);
            auto it = ums.find(makeDummy(i));
            if (it != ums.end()) it->print(); else cout << "Нет.\n";
            break;
        }
        case 6: { for (const auto& b : ums) b.print(); break; }
        case 7: { printSortedByPrice(ums.begin(), ums.end()); break; }
        case 8: {
            ofstream f("umset_books.txt"); f << ums.size() << "\n";
            for (const auto& b : ums) b.save(f);
            f.close(); cout << "OK\n"; break;
        }
        case 9: {
            ifstream f("umset_books.txt"); if (!f) { cout << "Нет файла\n"; break; }
            size_t n; f >> n; f.ignore(10000, '\n'); ums.clear();
            for (size_t i = 0; i < n; ++i) { Book b; b.load(f); ums.insert(b); }
            f.close(); cout << "OK\n"; break;
        }
        case 0: break;
        default: cout << "Неверный ввод.\n";
        }
    } while (choice != 0);
}