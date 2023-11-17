cmake_minimum_required(VERSION 3.26)
project(dsa_trabalho C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(dsa_trabalho
        addData.h
        filmes.c
        structure.h)
