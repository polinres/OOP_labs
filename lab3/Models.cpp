#include "Models.h"

// Author
Author::Author(std::string n, std::string c, int y)
    : fullName(n), country(c), birthYear(y) {
}

void Author::print() const {
    std::cout << fullName << " (" << country << ", " << birthYear << " г.р.)";
}

void Author::input() {
    std::cout << "  ФИО автора: ";
    std::getline(std::cin, fullName);
    std::cout << "  Страна: ";
    std::getline(std::cin, country);
    std::cout << "  Год рождения: ";
    std::cin >> birthYear;
    std::cin.ignore(10000, '\n');
}

void Author::save(std::ostream& os) const {
    os << fullName << "\n" << country << "\n" << birthYear << "\n";
}

void Author::load(std::istream& is) {
    std::getline(is, fullName);
    std::getline(is, country);
    is >> birthYear;
    is.ignore(10000, '\n');
}

// PrintProduct
PrintProduct::PrintProduct(std::string t, int y, int c, double p)
    : title(t), year(y), copies(c), price(p) {
}

void PrintProduct::print() const {
    std::cout << "Название: " << title
        << ", Год: " << year
        << ", Тираж: " << copies
        << ", Цена: " << std::fixed << std::setprecision(2) << price;
}

void PrintProduct::input() {
    std::cout << "  Название: ";
    std::getline(std::cin, title);
    std::cout << "  Год издания: ";
    std::cin >> year;
    std::cout << "  Тираж: ";
    std::cin >> copies;
    std::cout << "  Цена: ";
    std::cin >> price;
    std::cin.ignore(10000, '\n');
}

void PrintProduct::save(std::ostream& os) const {
    os << title << "\n" << year << "\n" << copies << "\n" << price << "\n";
}

void PrintProduct::load(std::istream& is) {
    std::getline(is, title);
    is >> year >> copies >> price;
    is.ignore(10000, '\n');
}

// Book 
Book::Book(std::string t, int y, int c, double p,
    std::string i, std::string g, Author a)
    : PrintProduct(t, y, c, p), isbn(i), genre(g), author(a) {
}

void Book::print() const {
    PrintProduct::print();
    std::cout << ", ISBN: " << isbn
        << ", Жанр: " << genre
        << ", Автор: ";
    author.print();
    std::cout << std::endl;
}

void Book::input() {
    PrintProduct::input();
    std::cout << "  ISBN: ";
    std::getline(std::cin, isbn);
    std::cout << "  Жанр: ";
    std::getline(std::cin, genre);
    std::cout << "  Данные автора:\n";
    author.input();
}

void Book::save(std::ostream& os) const {
    PrintProduct::save(os);
    os << isbn << "\n" << genre << "\n";
    author.save(os);
}

void Book::load(std::istream& is) {
    PrintProduct::load(is);
    std::getline(is, isbn);
    std::getline(is, genre);
    author.load(is);
}

bool Book::operator<(const Book& other) const {
    return this->price > other.price;   
}

bool Book::operator==(const Book& other) const {
    return this->isbn == other.isbn; 
}

// Magazine 
Magazine::Magazine(std::string t, int y, int c, double p, int issue, std::string period)
    : PrintProduct(t, y, c, p), issueNumber(issue), periodicity(period) {
}

void Magazine::print() const {
    PrintProduct::print();
    std::cout << ", Номер выпуска: " << issueNumber
        << ", Периодичность: " << periodicity << std::endl;
}

void Magazine::input() {
    PrintProduct::input();
    std::cout << "  Номер выпуска: ";
    std::cin >> issueNumber;
    std::cin.ignore(10000, '\n');
    std::cout << "  Периодичность (напр. 'ежемесячный'): ";
    std::getline(std::cin, periodicity);
}

void Magazine::save(std::ostream& os) const {
    PrintProduct::save(os);
    os << issueNumber << "\n" << periodicity << "\n";
}

void Magazine::load(std::istream& is) {
    PrintProduct::load(is);
    is >> issueNumber;
    is.ignore(10000, '\n');
    std::getline(is, periodicity);
}

// PublishingHouse
PublishingHouse::PublishingHouse(std::string n) : name(n) {}