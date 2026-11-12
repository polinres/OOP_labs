#pragma once
#include <iostream>
#include <string>
#include <vector>
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
    std::string getName() const { return fullName; }
};

class PrintProduct {
protected:
    std::string title;
    int year;
    int copies;
    double price;
public:
    PrintProduct(std::string t = "", int y = 0, int c = 0, double p = 0.0);
    virtual ~PrintProduct() {}

    virtual void print() const;
    virtual void input();
    virtual void save(std::ostream& os) const;
    virtual void load(std::istream& is);

    std::string getTitle() const { return title; }
    double getPrice() const { return price; }
};

class Book : public PrintProduct {
private:
    std::string isbn;
    std::string genre;
    Author author;
public:
    Book(std::string t = "", int y = 0, int c = 0, double p = 0.0,
        std::string isbn = "", std::string genre = "", Author a = Author());

    void print() const override;
    void input() override;
    void save(std::ostream& os) const override;
    void load(std::istream& is) override;

    std::string getISBN() const { return isbn; }
    Author getAuthor() const { return author; }

    bool operator<(const Book& other) const;
    bool operator==(const Book& other) const;
};

class Magazine : public PrintProduct {
private:
    int issueNumber;
    std::string periodicity;
public:
    Magazine(std::string t = "", int y = 0, int c = 0, double p = 0.0,
        int issue = 0, std::string period = "");

    void print() const override;
    void input() override;
    void save(std::ostream& os) const override;
    void load(std::istream& is) override;

    int getIssue() const { return issueNumber; }
};

class PublishingHouse {
public:
    std::string name;
    std::vector<Book> books;
    PublishingHouse(std::string n = "");
};