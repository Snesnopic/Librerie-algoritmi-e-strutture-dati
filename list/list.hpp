#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

template <typename Data>
class List :virtual public LinearContainer<Data>,
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

    struct Node
    {

        Data dato;
        Node* next = nullptr;

        /* ********************************************************************** */

        // Specific constructors
        Node() = default;
        Node(const Data& d);
        Node(Data&& d) noexcept;

        /* ********************************************************************** */

        // Copy constructor
        // ...

        // Move constructor
        // ...

        /* ********************************************************************** */

        // Destructor
        // ...

        /* ********************************************************************** */

        // Comparison operators
        // ...

        /* ********************************************************************** */

        // Specific member functions

        // ...

    };

    // ...

public:

    // Default constructor
    List() = default;

    /* ************************************************************************ */

    // Specific constructor
    List(const LinearContainer<Data> &lc); // A list obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    List(const List &l);

    // Move constructor
    List(List &&l) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~List();

    /* ************************************************************************ */

    // Copy assignment
    List& operator=(const List &l);

    // Move assignment
    List& operator=(List &&l) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const List &l) const noexcept;
    bool operator!=(const List &l) const noexcept;

    /* ************************************************************************ */

    // Specific member functions

    // type InsertAtFront(argument) specifier; // Copy of the value
    // type InsertAtFront(argument) specifier; // Move of the value
    // type RemoveFromFront() specifier; // (must throw std::length_error when empty)
    // type FrontNRemove() specifier; // (must throw std::length_error when empty)

    // type InsertAtBack(argument) specifier; // Copy of the value
    // type InsertAtBack(argument) specifier; // Move of the value

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
    void Map(MapFunctor,void*) override; // Override MappableContainer member
    /* ************************************************************************ */
    // Specific member functions (inherited from PreOrderMappableContainer)
    void MapPreOrder(MapFunctor,void*) override; // Override PreOrderMappableContainer member
    /* ************************************************************************ */
    // Specific member functions (inherited from PostOrderMappableContainer)
    void MapPostOrder(MapFunctor,void*) override; // Override PostOrderMappableContainer member
    /* ************************************************************************ */
    // Specific member functions (inherited from FoldableContainer)
    using typename FoldableContainer<Data>::FoldFunctor;
    void Fold(FoldFunctor,const void*,void*) const override; // Override FoldableContainer member
    /* ************************************************************************ */
    // Specific member functions (inherited from PreOrderFoldableContainer)
    void FoldPreOrder(FoldFunctor,const void*,void*) const override; // Override FoldableContainer member
    /* ************************************************************************ */
    // Specific member functions (inherited from PostOrderFoldableContainer)
    void FoldPostOrder(FoldFunctor,const void*,void*) const override; // Override FoldableContainer member
protected:

    // Auxiliary member functions (for PreOrderMappableContainer & PostOrderMappableContainer)

    void MapPreOrder(MapFunctor f,void*,Node*); // Accessory function executing from one point of the list onwards
    void MapPostOrder(MapFunctor f,void*,Node*); // Accessory function executing from one point of the list onwards

    /* ************************************************************************ */

    // Auxiliary member functions (for PreOrderFoldableContainer & PostOrderFoldableContainer)

    void FoldPreOrder(FoldFunctor f, const void*,void*,Node*) const; // Accessory function executing from one point of the list onwards
    void FoldPostOrder(FoldFunctor f, const void*,void*,Node*) const; // Accessory function executing from one point of the list onwards

};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
