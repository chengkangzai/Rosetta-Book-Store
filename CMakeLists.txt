cmake_minimum_required(VERSION 3.17)
project(Rosetta_Book_Store)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        Rosetta_Book_Store
        main.cpp
        Query/BookQuery.h
        Models/Book.h
        Exception/ModalNotFoundException.h
        Exception/InvalidQueryType.h
)