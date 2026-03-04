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
    if (tree == NULL) {
        return;
    }

    BSTNode* result = insertRec(tree->root, value);
    if (result == NULL) {
        // Ошибка malloc - дерево не изменилось
        return;
    }
    tree->root = result;
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

// Поиск минимального элемента в поддереве
static BSTNode* findMin(BSTNode* node)
{
    if (node == NULL) {
        return NULL;
    }

    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}

// Рекурсивная функция удаления
static BSTNode* deleteRec(BSTNode* node, int value)
{
    // Базовый случай: значение не найдено
    if (node == NULL) {
        return NULL;
    }

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

// Публичная функция удаления
void bstDelete(BST* tree, int value)
{
    if (tree == NULL || tree->root == NULL) {
        return;
    }

    tree->root = deleteRec(tree->root, value);
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
