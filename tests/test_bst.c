#include "../include/bst.h"
#include <assert.h>
#include <stdio.h>

// Прототипы тестов
void testCreateAndFree();
void testInsertAndContains();
void testDuplicateInsert();
void testBoundaryValues();
void testNullHandling();
void testMultipleOperations();

// Запуск всех тестов
int main()
{
    puts("Running tests for a binary search tree...\n");

    testCreateAndFree();
    testInsertAndContains();
    testDuplicateInsert();
    testBoundaryValues();
    testNullHandling();
    testMultipleOperations();

    puts("\nAll test passed!\n");
    return 0;
}

// Создание и освобождение дерева
void testCreateAndFree()
{
    printf("Test 1: Creating and releasing a tree... ");

    BST* tree = createBST();
    assert(tree != NULL);
    assert(tree->root == NULL);

    bstFree(tree);

    puts("OK");
}

// Вставка и проверка наличия элементов
void testInsertAndContains()
{
    printf("Test 2: Insertion and verification of availability... ");

    BST* tree = createBST();

    // Вставка элементов
    bstInsert(tree, 5);
    bstInsert(tree, 3);
    bstInsert(tree, 7);
    bstInsert(tree, 2);
    bstInsert(tree, 4);
    bstInsert(tree, 6);
    bstInsert(tree, 8);

    // Проверка существующих элементов
    assert(bstContains(tree, 5) == true);
    assert(bstContains(tree, 3) == true);
    assert(bstContains(tree, 7) == true);
    assert(bstContains(tree, 2) == true);
    assert(bstContains(tree, 4) == true);
    assert(bstContains(tree, 6) == true);
    assert(bstContains(tree, 8) == true);

    // Проверка отсутствующих элементов
    assert(bstContains(tree, 1) == false);
    assert(bstContains(tree, 9) == false);
    assert(bstContains(tree, 0) == false);

    bstFree(tree);
    puts("OK");
}

// Вставка дубликатов
void testDuplicateInsert()
{
    printf("Test 3: Inserting duplicates... ");

    BST* tree = createBST();

    bstInsert(tree, 10);
    assert(bstContains(tree, 10) == true);

    // Вставляем дубликат и проверяем, что дерево не изменилось
    bstInsert(tree, 10); // Дубликат

    // Должен по-прежнему содержать 10
    assert(bstContains(tree, 10) == true);

    // Вставляем другие элементы для проверки структуры
    bstInsert(tree, 5);
    bstInsert(tree, 15);

    assert(bstContains(tree, 5) == true);
    assert(bstContains(tree, 15) == true);

    bstFree(tree);
    puts("OK");
}

// Граничные значения
void testBoundaryValues()
{
    printf("Test 4: Boundary values... ");

    BST* tree = createBST();

    // Вставка максимальных и минимальных значений
    bstInsert(tree, 0);
    bstInsert(tree, 2147483647); // INT_MAX
    bstInsert(tree, -2147483648); // INT_MIN

    assert(bstContains(tree, 0) == true);
    assert(bstContains(tree, 2147483647) == true);
    assert(bstContains(tree, -2147483648) == true);
    assert(bstContains(tree, 1) == false);

    bstFree(tree);
    puts("OK");
}

// Обработка NULL указателей
void testNullHandling()
{
    printf("Test 5: Handling NULL pointers... ");

    // Тест с NULL деревом
    bstInsert(NULL, 10); // Не должна упасть
    bstContains(NULL, 10); // Должна вернуть false
    bstFree(NULL); // Не должна упасть

    // Проверка возврата false для NULL дерева
    assert(bstContains(NULL, 10) == false);

    // Создаём дерево и тестируем с NULL внутри
    BST* tree = createBST();

    // В пустом дереве ничего нет
    assert(bstContains(tree, 10) == false);

    bstFree(tree);
    puts("OK");
}

// Комплексное тестирование
void testMultipleOperations()
{
    printf("Test 6: Comprehensive testing... ");

    BST* tree = createBST();

    // Вставка в разном порядке
    int values[] = { 50, 30, 70, 20, 40, 60, 80, 10, 90, 45, 55, 85 };
    int numValues = sizeof(values) / sizeof(values[0]);

    for (int index = 0; index < numValues; ++index) {
        bstInsert(tree, values[index]);
    }

    // Проверка всех вставленных значений
    for (int index = 0; index < numValues; ++index) {
        assert(bstContains(tree, values[index]) == true);
    }

    // Проверка отсутствующих значений
    int notInTree[] = { 15, 25, 35, 65, 75, 95 };
    int numNotInTree = sizeof(notInTree) / sizeof(notInTree[0]);

    for (int index = 0; index < numNotInTree; ++index) {
        assert(bstContains(tree, notInTree[index]) == false);
    }

    bstFree(tree);
    puts("OK");
}
