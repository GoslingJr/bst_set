cmake_minimum_required(VERSION 3.10)
project(5.Stack-and-Quene)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(src/Stack)

add_executable(bracket_balance
     src/Task_1/Advancd-bracket-balance.c
     src/Stack/stack.c
)

add_executable(sorting_yard
     src/bst.c
     src/main.c
)
