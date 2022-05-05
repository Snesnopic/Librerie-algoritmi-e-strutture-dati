#include "./exercise1/test.hpp"

#include "./exercise2/test.hpp"
#include <chrono>
#include "./exercise3/test.hpp"
//
// #include "./exercise4/test.hpp"
//
// #include "./exercise5/test.hpp"

/* ************************************************************************** */

#include <iostream>

using namespace std;

/* ************************************************************************** */

void lasdtest()
{
    cout << endl << "~*~#~*~ Welcome to the LASD Test Suite ~*~#~*~ " << endl;
    auto t_start = std::chrono::high_resolution_clock::now();
    testSimpleExercise1();
    testFullExercise1();
    testSimpleExercise2();
    testFullExercise2();
    //testSimpleExercise3();
    //testFullExercise3();
    // testSimpleExercise4();
    // testFullExercise4();
    // testSimpleExercise5();
    // testFullExercise5();
    auto t_end = std::chrono::high_resolution_clock::now();
    cout << endl << "The test took "<<std::chrono::duration<double, std::milli>(t_end-t_start).count() /1000 << " seconds!";
    cout << endl << "Goodbye!" << endl;
}
