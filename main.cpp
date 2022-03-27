#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */
#ifndef Uint
#define Uint unsigned int
#else
#error
#endif
#include <iostream>

/* ************************************************************************** */

int main()
{
    std::cout << "Lasd Libraries 2022" << std::endl;
    lasdtest(); // To call in the menu of your library test!
    return 0;
}
