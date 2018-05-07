cmake_minimum_required(VERSION 3.10)
project(mastermind_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(mastermind
        src/autosolve.cpp
        src/autosolve.h
        src/catch.hpp
        src/code.cpp
        src/code.h
        src/score.cpp
        src/score.h
        src/main.cpp
        src/mastermind.cpp
        src/mastermind.h
        src/peg.cpp
        src/peg.h
        )

add_executable(tests
        src/autosolve.cpp
        src/autosolve.h
        src/catch.hpp
        src/code.cpp
        src/code.h
        src/score.cpp
        src/score.h
        src/tests.cpp
        src/mastermind.cpp
        src/mastermind.h
        src/peg.cpp
        src/peg.h
        )
