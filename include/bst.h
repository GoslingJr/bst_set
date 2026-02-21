#ifndef BST_H
#define BST_H

#include <stdbool.h>

// Структура узла бинарного дерева поиска
typedef struct BSTNode {
    int key;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

// Основная структура дерева
typedef struct BST {
    BSTNode *root;
} BST;

// Вставка значения в дерево
void bstInsert(BST *tree, int value);

// Проверка наличия значения в дереве
bool bstContains(BST *tree, int value);

// Освобождение памяти
void bstFree(BST *tree);

#endif
