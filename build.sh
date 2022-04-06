
#! /bin/bash

g++ -O3 -ggdb3 -Weffc++ -o main \
  zlasdtest/exercise1/simpletest.cpp zlasdtest/exercise1/fulltest.cpp \
  zlasdtest/container/container.cpp \
  zlasdtest/test.cpp zmytest/test.cpp main.cpp

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./main