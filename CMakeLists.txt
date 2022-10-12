cmake_minimum_required(VERSION 3.23)
project(TP5Kruskal C)

file(GLOB_RECURSE SOURCES src/*.c)
include_directories(include)
set(CMAKE_C_STANDARD 99)

add_executable(TP5Kruskal ${SOURCES} src/Kruskal.c include/Kruskal.h src/prim.c include/prim.h)

