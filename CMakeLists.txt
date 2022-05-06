cmake_minimum_required(VERSION 3.14)
project(Librerie_algoritmi_e_strutture_dati)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_CXX_FLAGS -O0)
set(CMAKE_CXX_FLAGS -ggdb)
set(CMAKE_CXX_FLAGS --coverage)

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
include_directories(stack)
include_directories(stack/lst)
include_directories(stack/vec)
include_directories(vector)
include_directories(zlasdtest)
include_directories(zlasdtest/binarytree)
include_directories(zlasdtest/container)
include_directories(zlasdtest/exercise1)
include_directories(zlasdtest/exercise2)
include_directories(zlasdtest/exercise3)
include_directories(zlasdtest/iterator)
include_directories(zlasdtest/list)
include_directories(zlasdtest/queue)
include_directories(zlasdtest/stack)
include_directories(zlasdtest/vector)
include_directories(zmytest)

add_executable(Librerie_algoritmi_e_strutture_dati
        zlasdtest/container/container.cpp
        zlasdtest/exercise1/fulltest.cpp
        zlasdtest/exercise1/simpletest.cpp
        zlasdtest/exercise2/fulltest.cpp
        zlasdtest/exercise2/simpletest.cpp
        zlasdtest/exercise3/fulltest.cpp
        zlasdtest/exercise3/simpletest.cpp
        zlasdtest/test.cpp
        zmytest/test.cpp
        main.cpp)
