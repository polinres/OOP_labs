#pragma once
#include <iostream>
#include <string>

std::string readLine(const std::string& prompt);
int readInt(const std::string& prompt);

enum ProductType { BOOK, MAGAZINE, NEWSPAPER, BROCHURE, POSTER };

// Обложки (для полиморфной фабрики) 
class Cover {
public:
    virtual ~Cover() {}
    virtual std::string name() const = 0;
};
class HardCover : public Cover {
public:
    std::string name() const { return "твердый переплет"; }
};
class SoftCover : public Cover {
public:
    std::string name() const { return "мягкая обложка"; }
};
class NoCover : public Cover {
public:
    std::string name() const { return "без обложки"; }
};

// Параметры для фабричного метода с аргументами 
class ProductSpec {
public:
    std::string title;
    int copies = 0;
    virtual ~ProductSpec() {}
    virtual ProductType productType() const = 0;
};
class BookSpec : public ProductSpec {
public:
    std::string author;
    ProductType productType() const { return BOOK; }
};
class MagazineSpec : public ProductSpec {
public:
    int issue = 0;
    ProductType productType() const { return MAGAZINE; }
};
class NewspaperSpec : public ProductSpec {
public:
    std::string city;
    ProductType productType() const { return NEWSPAPER; }
};
class BrochureSpec : public ProductSpec {
public:
    std::string topic;
    ProductType productType() const { return BROCHURE; }
};
class PosterSpec : public ProductSpec {
public:
    std::string format;
    ProductType productType() const { return POSTER; }
};

// Печатная продукция 
class PrintedProduct {
protected:
    std::string title;
    int copies;
public:
    PrintedProduct(std::string t = "", int c = 0) : title(t), copies(c) {}
    virtual ~PrintedProduct() {}
    virtual void print() const = 0;
    virtual void input();
    virtual void save(std::ostream& os) const = 0;
    virtual PrintedProduct* clone() const = 0; // полиморфное копирование
    virtual Cover* makeCover() const = 0; // полиморфная фабрика
};

class Book : public PrintedProduct {
    std::string author;
public:
    Book() {}
    Book(const BookSpec* s) : PrintedProduct(s->title, s->copies), author(s->author) {}
    void print() const;
    void input();
    void save(std::ostream& os) const;
    Book* clone() const { return new Book(*this); }
    HardCover* makeCover() const { return new HardCover; }
    static PrintedProduct* makeProduct() { return new Book; }
    static void Register();
};

class Magazine : public PrintedProduct {
    int issue;
public:
    Magazine() : issue(0) {}
    Magazine(const MagazineSpec* s) : PrintedProduct(s->title, s->copies), issue(s->issue) {}
    void print() const;
    void input();
    void save(std::ostream& os) const;
    Magazine* clone() const { return new Magazine(*this); }
    SoftCover* makeCover() const { return new SoftCover; }
    static PrintedProduct* makeProduct() { return new Magazine; }
    static void Register();
};

class Newspaper : public PrintedProduct {
    std::string city;
public:
    Newspaper() {}
    Newspaper(const NewspaperSpec* s) : PrintedProduct(s->title, s->copies), city(s->city) {}
    void print() const;
    void input();
    void save(std::ostream& os) const;
    Newspaper* clone() const { return new Newspaper(*this); }
    NoCover* makeCover() const { return new NoCover; }
    static PrintedProduct* makeProduct() { return new Newspaper; }
    static void Register();
};

class Brochure : public PrintedProduct {
    std::string topic;
public:
    Brochure() {}
    Brochure(const BrochureSpec* s) : PrintedProduct(s->title, s->copies), topic(s->topic) {}
    void print() const;
    void input();
    void save(std::ostream& os) const;
    Brochure* clone() const { return new Brochure(*this); }
    SoftCover* makeCover() const { return new SoftCover; }
    static PrintedProduct* makeProduct() { return new Brochure; }
    static void Register();
};

class Poster : public PrintedProduct {
    std::string format;
public:
    Poster() {}
    Poster(const PosterSpec* s) : PrintedProduct(s->title, s->copies), format(s->format) {}
    void print() const;
    void input();
    void save(std::ostream& os) const;
    Poster* clone() const { return new Poster(*this); }
    NoCover* makeCover() const { return new NoCover; }
    static PrintedProduct* makeProduct() { return new Poster; }
    static void Register();
};