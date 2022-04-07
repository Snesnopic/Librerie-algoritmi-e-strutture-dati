
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst {
                  // Must extend Stack<Data>,
                  //             List<Data>

private:

  // ...

protected:

  // using List<Data>::???;

  // ...

public:

  // Default constructor
  // StackLst() specifier;

  /* ************************************************************************ */

  // Specific constructor
  // StackLst(argument) specifiers; // A stack obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  // StackLst(argument);

  // Move constructor
  // StackLst(argument);

  /* ************************************************************************ */

  // Destructor
  // ~StackLst() specifier;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument);

  // Move assignment
  // type operator=(argument);

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  // type Top() specifiers; // Override Stack member (constant version; must throw std::length_error when empty)
  // type Top() specifiers; // Override Stack member (must throw std::length_error when empty)
  // type Pop() specifiers; // Override Stack member (must throw std::length_error when empty)
  // type TopNPop() specifiers; // Override Stack member (must throw std::length_error when empty)
  // type Push(argument) specifiers; // Override Stack member (copy of the value)
  // type Push(argument) specifiers; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  // type Clear() specifiers; // Override Container member

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
