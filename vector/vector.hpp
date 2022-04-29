#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

    template<typename Data>
    class Vector
            : virtual public LinearContainer<Data>,
              virtual public PreOrderMappableContainer<Data>,
              virtual public PostOrderMappableContainer<Data>,
              virtual public PreOrderFoldableContainer<Data>,
              virtual public PostOrderFoldableContainer<Data>
    {
        // Must extend LinearContainer<Data>,
        //             PreOrderMappableContainer<Data>,
        //             PostOrderMappableContainer<Data>,
        //             PreOrderFoldableContainer<Data>,
        //             PostOrderFoldableContainer<Data>

    private:

        // ...

    protected:

        using LinearContainer<Data>::size;
        Data *array = nullptr;
        // ...

    public:

        // Default constructor
        Vector() = default;

        /* ************************************************************************ */

        // Specific constructors
        Vector(const unsigned long initialSize); // A vector with a given initial dimension
        Vector(const LinearContainer<Data>& lc); // A vector obtained from a LinearContainer

        /* ************************************************************************ */

        // Copy constructor
        Vector(const Vector& v);

        // Move constructor
        Vector(Vector&& v) noexcept;

        /* ************************************************************************ */

        // Destructor
        virtual ~Vector();

        /* ************************************************************************ */

        // Copy assignment
        Vector& operator=(const Vector& v);

        // Move assignment
        Vector& operator=(Vector&& v) noexcept;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const Vector& v) const noexcept;

        bool operator!=(const Vector& v) const noexcept;

        /* ************************************************************************ */

        // Specific member functions

        void Resize(const unsigned long newSize); // Resize the vector to a given size

        /* ************************************************************************ */

        // Specific member functions (inherited from Container)

        void Clear() override; // Override Container member

        /* ************************************************************************ */

        // Specific member functions (inherited from LinearContainer)

        Data& Front() const override; // Override LinearContainer member (must throw std::length_error when empty)
        Data& Back() const override; // Override LinearContainer member (must throw std::length_error when empty)

        Data& operator[](const unsigned long index) const override; // Override LinearContainer member (must throw std::out_of_range when out of range)

        /* ************************************************************************ */

        // Specific member functions (inherited from MappableContainer)

        using typename MappableContainer<Data>::MapFunctor;

        void Map(MapFunctor f, void *par) override; // Override MappableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from PreOrderMappableContainer)

        void MapPreOrder(MapFunctor f, void *par) override; // Override PreOrderMappableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from PostOrderMappableContainer)

        void MapPostOrder(MapFunctor f, void *par) override; // Override PostOrderMappableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from FoldableContainer)

        using typename FoldableContainer<Data>::FoldFunctor;

        void Fold(FoldFunctor f, const void *par, void *acc) const override; // Override FoldableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from PreOrderFoldableContainer)

        void FoldPreOrder(FoldFunctor f, const void *par, void *acc) const override; // Override FoldableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from PostOrderFoldableContainer)

        void FoldPostOrder(FoldFunctor f, const void *par, void *acc) const override; // Override FoldableContainer member

    };

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
