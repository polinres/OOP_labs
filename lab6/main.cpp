#include <iostream>
#include <fstream>
#include <vector>
#include "ProductFactories.h"
using namespace std;

vector<PrintedProduct*> items;

ProductType chooseType() {
    cout << "Тип: 1-Книга 2-Журнал 3-Газета 4-Брошюра 5-Плакат\n";
    int t;
    do { t = readInt("Выбор типа: "); } while (t < 1 || t > 5);
    return (ProductType)(t - 1);
}

// Заполнение параметров для фабричного метода с аргументами
ProductSpec* askSpec(ProductType type) {
    ProductSpec* spec = nullptr;
    switch (type) {
    case BOOK: { BookSpec* s = new BookSpec; s->author = ""; spec = s; break; }
    case MAGAZINE: spec = new MagazineSpec; break;
    case NEWSPAPER: spec = new NewspaperSpec; break;
    case BROCHURE: spec = new BrochureSpec; break;
    case POSTER: spec = new PosterSpec; break;
    }
    spec->title = readLine("  Название: ");
    spec->copies = readInt("  Тираж: ");
    switch (type) {
    case BOOK: static_cast<BookSpec*>(spec)->author = readLine("  Автор: "); break;
    case MAGAZINE: static_cast<MagazineSpec*>(spec)->issue = readInt("  Номер выпуска: "); break;
    case NEWSPAPER: static_cast<NewspaperSpec*>(spec)->city = readLine("  Город издания: "); break;
    case BROCHURE: static_cast<BrochureSpec*>(spec)->topic = readLine("  Тема: "); break;
    case POSTER: static_cast<PosterSpec*>(spec)->format = readLine("  Формат: "); break;
    }
    return spec;
}

void showAll() {
    if (items.empty()) { cout << "Список пуст.\n"; return; }
    for (size_t i = 0; i < items.size(); ++i) {
        cout << "[" << i + 1 << "] ";
        items[i]->print();
    }
}

int askIndex() {
    int n = readInt("Номер элемента: ");
    if (n < 1 || n >(int)items.size()) { cout << "Нет такого элемента.\n"; return -1; }
    return n - 1;
}

int main() {
    system("chcp 1251 > nul");
    system("cls");

    // регистрация типов в реестре
    Book::Register();
    Magazine::Register();
    Newspaper::Register();
    Brochure::Register();
    Poster::Register();

    int choice;
    do {
        cout << "\n--- УЧЕТ ПЕЧАТНОЙ ПРОДУКЦИИ ИЗДАТЕЛЬСТВА ---\n"
            << "1. Добавить (фабричный метод)\n"
            << "2. Добавить (фабричный метод с аргументами)\n"
            << "3. Добавить (фабричный конструктор, по номеру типа)\n"
            << "4. Копировать элемент (полиморфное копирование)\n"
            << "5. Создать обложку для элемента (полиморфная фабрика)\n"
            << "6. Показать все\n"
            << "7. Редактировать\n"
            << "8. Удалить\n"
            << "9. Сохранить в файл\n"
            << "0. Выход\n"
            << "Выбор: ";
        cin >> choice;
        cin.ignore(10000, '\n');

        switch (choice) {
        case 1: {
            PrintedProduct* p = makeProduct(chooseType());
            p->input();
            items.push_back(p);
            cout << "Добавлено.\n";
            break;
        }
        case 2: {
            ProductSpec* spec = askSpec(chooseType());
            items.push_back(makeProductWithSpec(spec));
            delete spec;
            cout << "Добавлено.\n";
            break;
        }
        case 3: {
            int id = readInt("Номер типа в реестре (0-" + to_string(registrySize() - 1) + "): ");
            PrintedProduct* p = makeRegisteredProduct(id);
            if (!p) { cout << "Тип не найден.\n"; break; }
            p->input();
            items.push_back(p);
            cout << "Добавлено.\n";
            break;
        }
        case 4: {
            int i = askIndex();
            if (i < 0) break;
            items.push_back(items[i]->clone());
            cout << "Копия добавлена в конец списка.\n";
            break;
        }
        case 5: {
            int i = askIndex();
            if (i < 0) break;
            Cover* c = items[i]->makeCover();
            cout << "Создана обложка: " << c->name() << "\n";
            delete c;
            break;
        }
        case 6: showAll(); break;
        case 7: {
            int i = askIndex();
            if (i < 0) break;
            cout << "Введите новые данные:\n";
            items[i]->input();
            cout << "Отредактировано.\n";
            break;
        }
        case 8: {
            int i = askIndex();
            if (i < 0) break;
            delete items[i];
            items.erase(items.begin() + i);
            cout << "Удалено.\n";
            break;
        }
        case 9: {
            ofstream f("products.txt");
            if (!f) { cout << "Ошибка файла!\n"; break; }
            for (size_t i = 0; i < items.size(); ++i) items[i]->save(f);
            cout << "Сохранено элементов: " << items.size() << "\n";
            break;
        }
        case 0: cout << "Выход...\n"; break;
        default: cout << "Неверный ввод!\n";
        }
    } while (choice != 0);

    for (size_t i = 0; i < items.size(); ++i) delete items[i];
    return 0;
}