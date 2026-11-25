#pragma once
#include <vector>
#include <utility>
#include "Classes.h"

// 1. Фабричный метод
PrintedProduct* makeProduct(ProductType type);

// 2. Фабричный метод с аргументами
PrintedProduct* makeProductWithSpec(const ProductSpec* spec);

// 3. Фабричный конструктор (динамический реестр типов)
typedef PrintedProduct* (*ProductFactory)();
void RegisterProduct(ProductFactory factory);
PrintedProduct* makeRegisteredProduct(int id);
int registrySize();