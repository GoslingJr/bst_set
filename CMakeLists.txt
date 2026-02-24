cmake_minimum_required(VERSION 3.10)
project(BinarySearchTree)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Исполняемые файлы в build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(program src/main.c src/bst.c)

add_executable(test_bst tests/test_bst.c src/bst.c)

# test_bst тоже в build/bin
set_target_properties(test_bst PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
