#! /bin/bash

g++ -O3 -std=c++17 -o main \
  zlasdtest/exercise1/simpletest.cpp \
  zlasdtest/exercise2/simpletest.cpp \
  zlasdtest/exercise3/simpletest.cpp \
  zlasdtest/exercise4/simpletest.cpp \
  zlasdtest/exercise5/simpletest.cpp \
  zlasdtest/container/container.cpp \
  zlasdtest/test.cpp zmytest/test.cpp main.cpp