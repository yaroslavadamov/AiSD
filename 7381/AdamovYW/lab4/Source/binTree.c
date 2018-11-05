#include <stdlib.h>
#include "binTree.h"


// Возврат левого поддерева.
BinTree* leftBinTree(BinTree* binTree){
    if (binTree != NULL)
        return binTree->leftTree;
    else
        return NULL;
}

// Возврат правого поддерева.
BinTree* rightBinTree(BinTree* binTree){
    if (binTree != NULL)
        return binTree->rightTree;
    else
        return NULL;
}

// Создание дерева.
BinTree* initBinTree(char a){
    BinTree* binTree = (BinTree*)malloc(sizeof(BinTree));
    binTree->a = a;
    binTree->leftTree = NULL;
    binTree->rightTree = NULL;
    return binTree;
}

// Поиск по дереву.
BinTree* findBinTree(BinTree* binTree, char a){
    if (binTree == NULL)
        return NULL;
    if (binTree->a == a)
        return binTree;
    if (findBinTree(leftBinTree(binTree), a) == NULL)
        return findBinTree(rightBinTree(binTree), a);
    else
        return findBinTree(leftBinTree(binTree), a);
}

// Глубина дерева.
int binTreeDeepLevel(BinTree* binTree){
    if (binTree == NULL)
        return 0;
    int leftDeep = binTreeDeepLevel(leftBinTree(binTree));
    int rightDeep = binTreeDeepLevel(rightBinTree(binTree));
    return 1 + (leftDeep > rightDeep ? leftDeep : rightDeep);
}