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
