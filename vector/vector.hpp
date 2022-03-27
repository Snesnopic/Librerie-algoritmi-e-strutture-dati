#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public LinearContainer<Data>, virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data>, virtual public PreOrderFoldableContainer<Data>, virtual public PostOrderFoldableContainer<Data>
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
    Data *array;
    // ...

public:

    // Default constructor
    Vector();

    /* ************************************************************************ */

    // Specific constructors
    Vector<Data>(unsigned long initialSize); // A vector with a given initial dimension
    Vector<Data>(LinearContainer<Data> lc); // A vector obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    Vector<Data>(const Vector<Data> &v);

    // Move constructor
    Vector<Data>(Vector<Data> &&v);

    /* ************************************************************************ */

    // Destructor
    ~Vector();

    /* ************************************************************************ */

    // Copy assignment
    Vector& operator=(const Vector v);

    // Move assignment
    Vector& operator=(Vector &&v);

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const Vector &v);
    bool operator!=(const Vector &v);

    /* ************************************************************************ */

    // Specific member functions

    void Resize(const unsigned long newSize); // Resize the vector to a given size

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    void Clear() override; // Override Container member

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    // type Front() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
    // type Back() specifiers; // Override LinearContainer member (must throw std::length_error when empty)

    Data& operator[](const unsigned long index); // Override LinearContainer member (must throw std::out_of_range when out of range)

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    using typename MappableContainer<Data>::MapFunctor;

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
