#pragma once

#include <stdbool.h>

// Структура узла бинарного дерева поиска
typedef struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Основная структура дерева
typedef struct BST {
    BSTNode* root;
} BST;

// Создание бинарного дерева поиска
BST* createBST(void);

// Вставка значения в дерево
void bstInsert(BST* tree, int value);

// Проверка наличия значения в дереве
bool bstContains(BST* tree, int value);

// Освобождение памяти
void bstFree(BST* tree);

// Симметричный обход (in-order)
void bstInorder(BST* tree);

// Прямой обход (pre-order)
void bstPreorder(BST* tree);

// Обратный обход (post-order)
void bstPostorder(BST* tree);

// Высота дерева (количество уровней)
// Пустое дерево имеет высоту 0
int bstHeight(BST* tree);

// Количество узлов в дереве
int bstSize(BST* tree);

// Минимальное значение в дереве
// Вызов на пустом дереве приводит к аварийному завершению программы
int bstMin(BST* tree);

// Максимальное значение в дереве
// Вызов на пустом дереве приводит к аварийному завершению программы
int bstMax(BST* tree);
