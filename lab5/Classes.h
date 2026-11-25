#pragma once
#include <iostream>
#include <string>
#include <iomanip>

class Author {
private:
    std::string fullName;
    std::string country;
    int birthYear;
public:
    Author(std::string n = "", std::string c = "", int y = 0);
    void print() const;
    void input();
    void save(std::ostream& os) const;
    void load(std::istream& is);
};

class Book {
private:
    std::string title;
    int year;
    int copies;
    double price;
    std::string isbn;
    std::string genre;
    Author author;

public:
    Book(std::string t = "", int y = 0, int c = 0, double p = 0.0,
        std::string i = "", std::string g = "", Author a = Author());

    void print() const;
    void input();
    void save(std::ostream& os) const;
    void load(std::istream& is);

    std::string getISBN() const { return isbn; }
    std::string getGenre() const { return genre; }
    double getPrice() const { return price; }

    bool operator<(const Book& other) const {
        return this->price < other.price;
    }

    bool operator==(const Book& other) const {
        return this->isbn == other.isbn;
    }
};