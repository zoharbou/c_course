cmake_minimum_required(VERSION 3.9.6)
project(ex2 C)

set(CMAKE_C_STANDARD 99)

add_executable(ex2 battleships.c battleships.h battleships_game.c)
