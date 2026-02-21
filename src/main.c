#include <stdio.h>
#include "bst.h"
#include <stdio.h>

int main() {
    // Создаём дерево
    BST tree = {NULL};

    // Вставляем элементы
    bstInsert(&tree, 10);
    bstInsert(&tree, 5);
    bstInsert(&tree, 15);
    bstInsert(&tree, 3);
    bstInsert(&tree, 7);
    bstInsert(&tree, 12);
    bstInsert(&tree, 18);

    // Проверяем наличие
    printf("10? %s\n", bstContains(&tree, 10) ? "Да" : "Нет");
    printf("7? %s\n", bstContains(&tree, 7) ? "Да" : "Нет");
    printf("20? %s\n", bstContains(&tree, 20) ? "Да" : "Нет");
    printf("3? %s\n", bstContains(&tree, 3) ? "Да" : "Нет");

    // Проверка дубликата
    bstInsert(&tree, 10);
    printf("После дублирования 10, всеё ещё содержит 10? %s\n", bstContains(&tree, 10) ? "Да" : "Нет");

    // Освобождаем память
    bstFree(&tree);
    printf("После освобождения 10? %s\n", bstContains(&tree, 10) ? "Да" : "Нет");

    return 0;
}
