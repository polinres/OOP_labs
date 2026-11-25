#include "ProductFactories.h"

int productTypeCount = 0; // счетчик типов
std::vector<std::pair<int, ProductFactory>> productRegistry;

// 1. Фабричный метод
PrintedProduct* makeProduct(ProductType type) {
    switch (type) {
    case BOOK: return new Book();
    case MAGAZINE: return new Magazine();
    case NEWSPAPER: return new Newspaper();
    case BROCHURE: return new Brochure();
    case POSTER: return new Poster();
    }
    return nullptr;
}

// 2. Фабричный метод с аргументами
PrintedProduct* makeProductWithSpec(const ProductSpec* spec) {
    switch (spec->productType()) {
    case BOOK: return new Book(static_cast<const BookSpec*>(spec));
    case MAGAZINE: return new Magazine(static_cast<const MagazineSpec*>(spec));
    case NEWSPAPER: return new Newspaper(static_cast<const NewspaperSpec*>(spec));
    case BROCHURE: return new Brochure(static_cast<const BrochureSpec*>(spec));
    case POSTER: return new Poster(static_cast<const PosterSpec*>(spec));
    }
    return nullptr;
}

// 3. Фабричный конструктор
void RegisterProduct(ProductFactory factory) {
    productRegistry.push_back(std::make_pair(productTypeCount++, factory));
}

PrintedProduct* makeRegisteredProduct(int id) {
    if (id < 0 || id >= (int)productRegistry.size()) return nullptr;
    ProductFactory factory = productRegistry[id].second;
    return factory();
}

int registrySize() { return (int)productRegistry.size(); }

void Book::Register() { RegisterProduct(Book::makeProduct); }
void Magazine::Register() { RegisterProduct(Magazine::makeProduct); }
void Newspaper::Register() { RegisterProduct(Newspaper::makeProduct); }
void Brochure::Register() { RegisterProduct(Brochure::makeProduct); }
void Poster::Register() { RegisterProduct(Poster::makeProduct); }