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

// Публичная функция рекурсивной вставки
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

// Публичная функция рекурсивной проверки наличия
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

// Публичная функция очистки дерева
void bstFree(BST* tree)
{
    if (tree != NULL) {
        freeRec(tree->root);
        tree->root = NULL;
        free(tree);
    }
}

// Рекурсивный симметричный обход (in-order): левое поддерево -> узел -> правое поддерево
static void inorderRec(BSTNode* node)
{
    if (node == NULL)
        return;

    inorderRec(node->left);
    printf("%d ", node->key);
    inorderRec(node->right);
}

// Публичная функция симметричного обхода
void bstInorder(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        puts("Tree is empty");
        return;
    }

    printf("Symmetric traversal (in-order): ");
    inorderRec(tree->root);
    puts("");
}

// Рекурсивный прямой обход (pre-order): узел -> левое поддерево -> правое поддерево
static void preorderRec(BSTNode* node)
{
    if (node == NULL)
        return;

    printf("%d ", node->key);
    preorderRec(node->left);
    preorderRec(node->right);
}

// Публичная функция прямого обхода
void bstPreorder(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        puts("Tree is empty");
        return;
    }

    printf("Direct traversal (pre-order): ");
    preorderRec(tree->root);
    puts("");
}

// Рекурсивный обратный обход (post-order): левое поддерево -> правое поддерево -> узел
static void postorderRec(BSTNode* node)
{
    if (node == NULL)
        return;

    postorderRec(node->left);
    postorderRec(node->right);
    printf("%d ", node->key);
}

// Публичная функция обратного обхода
void bstPostorder(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        puts("Tree is empty");
        return;
    }

    printf("Reverse traversal (post-order): ");
    postorderRec(tree->root);
    puts("");
}