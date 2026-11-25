#include "Classes.h"

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