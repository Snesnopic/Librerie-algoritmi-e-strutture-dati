cmake_minimum_required(VERSION 3.14)
project(LASD DESCRIPTION "Libreria Algoritmi e Strutture Dati")

SET(CMAKE_CXX_STANDARD 20)
SET(CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(.)
include_directories(binarytree)
include_directories(binarytree/lnk)
include_directories(binarytree/vec)
include_directories(container)
include_directories(iterator)
include_directories(list)
include_directories(queue)
include_directories(queue/lst)
include_directories(queue/vec)
include_directories(graph)
include_directories(graph/graphmtrx)
include_directories(graph/graphlst)
include_directories(bimap)
include_directories(stack)
include_directories(stack/lst)
include_directories(stack/vec)
include_directories(vector)
include_directories(matrix)
include_directories(matrix/valmatrix)
include_directories(bst)
include_directories(hashtable)
include_directories(hashtable/opnadr)
include_directories(hashtable/clsadr)
include_directories(zlasdtest)
include_directories(zlasdtest/binarytree)
include_directories(zlasdtest/container)
include_directories(zlasdtest/exercise1)
include_directories(zlasdtest/exercise2)
include_directories(zlasdtest/exercise3)
include_directories(zlasdtest/exercise4)
include_directories(zlasdtest/exercise5)
include_directories(zlasdtest/iterator)
include_directories(zlasdtest/hashtable)
include_directories(zlasdtest/list)
include_directories(zlasdtest/queue)
include_directories(zlasdtest/stack)
include_directories(zlasdtest/vector)
include_directories(zlasdtest/bst)
include_directories(zmytest)

add_executable(LASD
        zlasdtest/container/container.cpp
        zlasdtest/exercise1/simpletest.cpp
        zlasdtest/exercise2/simpletest.cpp
        zlasdtest/exercise3/simpletest.cpp
        zlasdtest/exercise4/simpletest.cpp
        zlasdtest/exercise5/simpletest.cpp
        zlasdtest/test.cpp
        zmytest/test.cpp
        main.cpp)



