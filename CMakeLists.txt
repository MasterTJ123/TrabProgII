cmake_minimum_required(VERSION 4.0)
project(TrabProgII C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(TrabProgII snake.c snake.h ListaDinamicaEncadeada.h ListaDinamicaEncadeada.c)

find_package(raylib REQUIRED)

target_link_libraries(TrabProgII PRIVATE raylib m)