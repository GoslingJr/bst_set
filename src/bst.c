#include "../include/bst.h"
#include <stdio.h>
#include <stdlib.h>

// Создание бинарного дерева поиска
BST* createBST(void)
{
    BST* bst = malloc(sizeof(BST));
    if (bst == NULL) {
        return NULL;
    }
    bst->root = NULL;
    return bst;
}

// Рекурсивная вставка
static BSTNode* insertRec(BSTNode* node, int value)
{
    if (node == NULL) {
        BSTNode* newNode = malloc(sizeof(BSTNode));
        if (newNode == NULL) {
            // Возвращение существующего поддерева без изменений
            return node;
        }
        newNode->key = value;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (value < node->key)
        node->left = insertRec(node->left, value);
    else if (value > node->key)
        node->right = insertRec(node->right, value);
    return node;
}

// Обертка рекурсивной функции вставки
void bstInsert(BST* tree, int value)
{
    if (tree != NULL)
        tree->root = insertRec(tree->root, value);
}

// Рекурсивная проверка наличия
static bool containsRec(BSTNode* node, int value)
{
    if (node == NULL) {
        return false;
    }
    if (value == node->key) {
        return true;
    }
    if (value < node->key) {
        return containsRec(node->left, value);
    } else {
        return containsRec(node->right, value);
    }
}

// Обертка функции рекурсивной проверки наличия
bool bstContains(BST* tree, int value)
{
    if (tree == NULL)
        return false;
    return containsRec(tree->root, value);
}

// Рекурсивная очистка
static void freeRec(BSTNode* node)
{
    if (node == NULL)
        return;
    freeRec(node->left);
    freeRec(node->right);
    free(node);
}

// Обертка функции очистки дерева
void bstFree(BST* tree)
{
    if (tree != NULL) {
        freeRec(tree->root);
        tree->root = NULL;
        free(tree);
    }
}

// Поиск минимального элемента в поддереве
static BSTNode* findMin(BSTNode* node)
{
    if (node == NULL)
        return NULL;

    while (node->left != NULL)
        node = node->left;

    return node;
}

// Рекурсивная функция удаления
static BSTNode* deleteRec(BSTNode* node, int value)
{
    // Базовый случай: значение не найдено
    if (node == NULL)
        return NULL;

    // Ищем удаляемый узел
    if (value < node->key) {
        // Идём в левое поддерево
        node->left = deleteRec(node->left, value);
    } else if (value > node->key) {
        // Идём в правое поддерево
        node->right = deleteRec(node->right, value);
    } else {
        // Нашли узел для удаления
        // Случай 1: узел - лист (нет потомков)
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        }

        // Случай 2: только правый потомок
        else if (node->left == NULL) {
            BSTNode* rightChild = node->right;
            free(node);
            return rightChild;
        }

        // Случай 2: только левый потомок
        else if (node->right == NULL) {
            BSTNode* leftChild = node->left;
            free(node);
            return leftChild;
        }

        // Случай 3: два потомка
        else {
            // Находим минимальный элемент в правом поддереве (это будет следующий по величине элемент)
            BSTNode* successor = findMin(node->right);

            // Копируем значение преемника в текущий узел
            node->key = successor->key;

            // Удаляем преемника из правого поддерева
            // (у него не может быть левого потомка, поэтому удаление будет простым)
            node->right = deleteRec(node->right, successor->key);
        }
    }

    return node;
}

// Обертка функции удаления
void bstDelete(BST* tree, int value)
{
    if (tree == NULL)
        return;

    tree->root = deleteRec(tree->root, value);
}