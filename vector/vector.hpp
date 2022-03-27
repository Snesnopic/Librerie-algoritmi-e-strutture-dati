#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public LinearContainer<Data>, PreOrderMappableContainer<Data>, PostOrderMappableContainer<Data>, PreOrderFoldableContainer<Data>, PostOrderFoldableContainer<Data>
{
    // Must extend LinearContainer<Data>,
    //             PreOrderMappableContainer<Data>,
    //             PostOrderMappableContainer<Data>,
    //             PreOrderFoldableContainer<Data>,
    //             PostOrderFoldableContainer<Data>

private:

    // ...

protected:

    // using LinearContainer<Data>::???;

    // ...

public:

    // Default constructor
    // Vector() specifiers;

    /* ************************************************************************ */

    // Specific constructors
    Vector(unsigned long initialSize); // A vector with a given initial dimension
    Vector(LinearContainer<Data> lc); // A vector obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    // Vector(argument) specifiers;

    // Move constructor
    // Vector(argument) specifiers;

    /* ************************************************************************ */

    // Destructor
    // ~Vector() specifiers;

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument) specifiers;

    // Move assignment
    // type operator=(argument) specifiers;

    /* ************************************************************************ */

    // Comparison operators
    friend bool operator==(const Vector &v1, const Vector &v2);
    friend bool operator!=(const Vector &v1, const Vector &v2);

    /* ************************************************************************ */

    // Specific member functions

    // type Resize(argument) specifiers; // Resize the vector to a given size

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    // type Clear() specifiers; // Override Container member

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    // type Front() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
    // type Back() specifiers; // Override LinearContainer member (must throw std::length_error when empty)

    // type operator[](argument) specifiers; // Override LinearContainer member (must throw std::out_of_range when out of range)

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    // using typename MappableContainer<Data>::MapFunctor;

    // type Map(arguments) specifiers; // Override MappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PreOrderMappableContainer)

    // type MapPreOrder(arguments) specifiers; // Override PreOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PostOrderMappableContainer)

    // type MapPostOrder(arguments) specifiers; // Override PostOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    // using typename FoldableContainer<Data>::FoldFunctor;

    // type Fold(arguments) specifiers; // Override FoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PreOrderFoldableContainer)

    // type FoldPreOrder(arguments) specifiers; // Override FoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PostOrderFoldableContainer)

    // type FoldPostOrder(arguments) specifiers; // Override FoldableContainer member

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
