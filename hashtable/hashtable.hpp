#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

    template<typename Data>
    class Hash
    {

    public:

        // type operator()(argument) specifiers; // (concrete function should not throw exceptions)

    };

/* ************************************************************************** */

    template<typename Data>
    class HashTable
    { // Must extend DictionaryContainer<Data>,
        //             MappableContainer<Data>,
        //             FoldableContainer<Data>

    private:

        // ...

    protected:

        // using DictionaryContainer<Data>::???;

        // ...

    public:

        // Destructor
        // ~HashTable() specifiers

        /* ************************************************************************ */

        // Copy assignment
        // type operator=(argument); // Copy assignment of abstract types should not be possible.

        // Move assignment
        // type operator=(argument); // Move assignment of abstract types should not be possible.

        /* ************************************************************************ */

        // Comparison operators
        // type operator==(argument) specifiers; // Comparison of abstract binary tree is possible.
        // type operator!=(argument) specifiers; // Comparison of abstract binary tree is possible.

        /* ************************************************************************ */

        // Specific member function

        // type Resize(argument) specifiers; // Resize the hashtable to a given size

    protected:

        // Auxiliary member functions

        // type HashKey(argument) specifiers;

    };

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
