#pragma once
#include "Models.h"
#include <functional>
#include <string>

// Компаратор: упорядочивание книг по ISBN (для set/multiset)
struct BookByISBN {
    bool operator()(const Book& a, const Book& b) const {
        return a.getISBN() < b.getISBN();
    }
};

// Хеш-функция для unordered_set/unordered_multiset
struct BookHash {
    size_t operator()(const Book& b) const {
        return std::hash<std::string>()(b.getISBN());
    }
};

// Функция сравнения на равенство для unordered_set/unordered_multiset
struct BookEqual {
    bool operator()(const Book& a, const Book& b) const {
        return a.getISBN() == b.getISBN();
    }
};

void demoMap();
void demoSet();
void demoMultiMap();
void demoMultiSet();
void demoUnorderedMap();
void demoUnorderedSet();
void demoUnorderedMultiMap();
void demoUnorderedMultiSet();