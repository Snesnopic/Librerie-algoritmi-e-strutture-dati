#! /bin/bash

g++ -O0 -ggdb3 -std=c++17 -g3 -o debug \
  zlasdtest/exercise1/simpletest.cpp zlasdtest/exercise1/fulltest.cpp \
  zlasdtest/exercise2/simpletest.cpp zlasdtest/exercise2/fulltest.cpp \
  zlasdtest/exercise3/simpletest.cpp zlasdtest/exercise3/fulltest.cpp \
  zlasdtest/container/container.cpp \
  zlasdtest/test.cpp zmytest/test.cpp main.cpp