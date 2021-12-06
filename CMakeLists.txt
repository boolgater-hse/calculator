cmake_minimum_required(VERSION 3.20)

project(calculator C)
set(CMAKE_C_STANDARD 11)

include_directories(include)

set(SOURCE_FILES src/main.c src/stack.c)
set(HEADER_FILES include/stack.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
if (UNIX)
    target_link_libraries(${PROJECT_NAME} m)
endif(UNIX)
