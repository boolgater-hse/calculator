# system
cmake_minimum_required(VERSION 3.19)
set(CMAKE_C_STANDARD 11)

# project
project(calculator C)

# sources
set(source_files src/main.c)

# build
add_executable(${PROJECT_NAME} src/main.c src/stack.c src/stack.h)
