cmake_minimum_required(VERSION 3.21)
project(Programmenwurf C)

set(CMAKE_C_STANDARD 11)

add_executable(Programmenwurf main.c functions.c functions.h draw.c draw.h)
