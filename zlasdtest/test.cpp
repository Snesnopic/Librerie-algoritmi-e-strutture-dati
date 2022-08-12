#include "./exercise1/test.hpp"

#include "./exercise2/test.hpp"

#include "./exercise3/test.hpp"

#include "./exercise4/test.hpp"

#include "./exercise5/test.hpp"

/* ************************************************************************** */

#include <iostream>

using namespace std;

/* ************************************************************************** */

void lasdtest()
{
	cout << endl << "~*~#~*~ Welcome to the LASD Test Suite ~*~#~*~ " << endl;
	unsigned int testnum = 0;
	unsigned int testerr = 0;
	testSimpleExercise1(testnum, testerr);
	testSimpleExercise2(testnum, testerr);
	testSimpleExercise3(testnum, testerr);
	testSimpleExercise4(testnum, testerr);
	testSimpleExercise5(testnum, testerr);
	cout << endl << "~*~#~*~ Results: " << testerr << " errors out of " << testnum << " tests! ~*~#~*~ " << endl;
	cout << endl << "Goodbye!" << endl;
}
