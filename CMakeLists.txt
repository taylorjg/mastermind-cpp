cmake_minimum_required(VERSION 3.10)
project(mastermind_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(mastermind
        src/autosolve.cc
        src/autosolve.h
        src/catch.hpp
        src/code.cc
        src/code.h
        src/feedback.cc
        src/feedback.h
        src/guess.cc
        src/guess.h
        src/main.cc
        src/mastermind.cc
        src/mastermind.h
        src/peg.cc
        src/peg.h
        src/secret.h)

add_executable(tests
        src/autosolve.cc
        src/autosolve.h
        src/catch.hpp
        src/code.cc
        src/code.h
        src/feedback.cc
        src/feedback.h
        src/guess.cc
        src/guess.h
        src/mastermind_tests.cc
        src/mastermind.cc
        src/mastermind.h
        src/peg.cc
        src/peg.h
        src/secret.h)
