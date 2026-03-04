#include "../include/bst.h"
#include <limits.h>
#include <stdbool.h>
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
            return NULL;
        }
        newNode->key = value;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (value < node->key) {
        node->left = insertRec(node->left, value);
    } else if (value > node->key) {
        node->right = insertRec(node->right, value);
    }
    return node;
}

// Публичная функция рекурсивной вставки
void bstInsert(BST* tree, int value)
{
    if (tree != NULL) {
        BSTNode* result = insertRec(tree->root, value);
        if (result == NULL && tree->root != NULL) {
            return;
        } else if (result != NULL) {
            tree->root = result;
        }
    }
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
    if (tree == NULL) {
        return false;
    }
    return containsRec(tree->root, value);
}

// Рекурсивная очистка
static void freeRec(BSTNode* node)
{
    if (node == NULL) {
        return;
    }
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
    if (node == NULL) {
        return;
    }

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
    if (node == NULL) {
        return;
    }

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
    if (node == NULL) {
        return;
    }

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

// Рекурсивное вычисление высоты дерева
static int heightRec(BSTNode* node)
{
    if (node == NULL) {
        return 0;
    }

    int leftHeight = heightRec(node->left);
    int rightHeight = heightRec(node->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Вычисление количества узлов в поддереве
static int sizeRec(BSTNode* node)
{
    if (node == NULL) {
        return 0;
    }

    return 1 + sizeRec(node->left) + sizeRec(node->right);
}

// Поиск минимального значения в поддереве
static int minRec(BSTNode* node)
{
    // Предполагается, что node не NULL
    while (node->left != NULL) {
        node = node->left;
    }

    return node->key;
}

// Поиск максимального значения в поддереве
static int maxRec(BSTNode* node)
{
    // Предполагается, что node не NULL
    while (node->right != NULL) {
        node = node->right;
    }

    return node->key;
}

// Публичая функция, возвращающая высоту дерева (пустое дерево имеет высоту 0)
int bstHeight(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        return 0;
    }

    return heightRec(tree->root);
}

// Публичая функция, возвращающая количество узлов в дереве
int bstSize(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        return 0;
    }

    return sizeRec(tree->root);
}

// Публичая функция, возвращающая минимальное значение в дереве
// Поведение на пустом дереве: завершает программу с сообщением об ошибке
int bstMin(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "Error: calling bstMin on an empty tree\n");
        exit(1);
    }

    return minRec(tree->root);
}

// Публичая функция, возвращающая максимальное значение в дереве
// Поведение на пустом дереве: завершает программу с сообщением об ошибке
int bstMax(BST* tree)
{
    if (tree == NULL || tree->root == NULL) {
        fprintf(stderr, "Error: calling bstMax on an empty tree\n");
        exit(1);
    }

    return maxRec(tree->root);
}

// Рекурсивная проверка с диапазоном допустимых значений
static bool isValidRec(BSTNode* node, int min, int max)
{
    // Пустое поддерево всегда корректно
    if (node == NULL) {
        return true;
    }

    // Проверяем текущий узел на соответствие диапазону
    if (node->key <= min || node->key >= max) {
        return false;
    }

    // Рекурсивно проверяем левое поддерево (все ключи должны быть меньше текущего)
    // и правое поддерево (все ключи должны быть больше текущего)
    return isValidRec(node->left, min, node->key) && isValidRec(node->right, node->key, max);
}

// Публичная функция проверки корректности BST
bool bstIsValid(BST* tree)
{
    // Пустое дерево считаем корректным BST
    if (tree == NULL || tree->root == NULL) {
        return true;
    }

    // Начинаем с минимально и максимально возможными значениями
    return isValidRec(tree->root, INT_MIN, INT_MAX);
}
