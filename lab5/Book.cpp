#include "Classes.h"

// Book
Book::Book(std::string t, int y, int c, double p, std::string i, std::string g, Author a)
    : title(t), year(y), copies(c), price(p), isbn(i), genre(g), author(a) {
}

void Book::print() const {
    std::cout << "ISBN: " << isbn
        << " | " << title
        << " | Год: " << year
        << " | Тираж: " << copies
        << " | Цена: " << std::fixed << std::setprecision(2) << price
        << " | Жанр: " << genre
        << " | Автор: ";
    author.print();
    std::cout << std::endl;
}

void Book::input() {
    std::cout << "  ISBN: ";
    std::getline(std::cin, isbn);
    std::cout << "  Название: ";
    std::getline(std::cin, title);
    std::cout << "  Год издания: ";
    std::cin >> year;
    std::cout << "  Тираж: ";
    std::cin >> copies;
    std::cout << "  Цена: ";
    std::cin >> price;
    std::cin.ignore(10000, '\n');
    std::cout << "  Жанр: ";
    std::getline(std::cin, genre);
    std::cout << "  Данные автора:\n";
    author.input();
}

void Book::save(std::ostream& os) const {
    os << isbn << "\n" << title << "\n" << year << "\n" << copies << "\n" << price << "\n" << genre << "\n";
    author.save(os);
}

void Book::load(std::istream& is) {
    std::getline(is, isbn);
    std::getline(is, title);
    is >> year >> copies >> price;
    is.ignore(10000, '\n');
    std::getline(is, genre);
    author.load(is);
}