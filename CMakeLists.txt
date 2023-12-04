cmake_minimum_required(VERSION 3.26)
project(ClionProjects C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ClionProjects
        addData.h
        filmes.c
        structure.h
)
