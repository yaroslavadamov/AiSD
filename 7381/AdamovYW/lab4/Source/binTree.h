#pragma once

// Структура бинарного дерева.
typedef struct BinTree{
    char a;
    struct BinTree* leftTree;
    struct BinTree* rightTree;
} BinTree;

// Возврат левого поддерева.
BinTree* leftBinTree(BinTree*);

// Возврат правого поддерева.
BinTree* rightBinTree(BinTree*);

// Создание дерева.
BinTree* initBinTree(char);

// Поиск по дереву.
BinTree* findBinTree(BinTree*, char);

// Глубина дерева.
int binTreeDeepLevel(BinTree*);