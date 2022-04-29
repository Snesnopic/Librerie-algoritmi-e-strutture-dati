#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

#include "../iterator/iterator.hpp"
#include "stack.hpp"
#include "queue.hpp"

// #include "..."

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

template <typename Data>
class BinaryTree: virtual public PreOrderMappableContainer<Data>,
                  virtual public PostOrderMappableContainer<Data>,
                  virtual public InOrderMappableContainer<Data>,
                  virtual public BreadthMappableContainer<Data>,
                  virtual public PreOrderFoldableContainer<Data>,
                  virtual public PostOrderFoldableContainer<Data>,
                  virtual public InOrderFoldableContainer<Data>,
                  virtual public BreadthFoldableContainer<Data>
{
    // Must extend PreOrderMappableContainer<Data>,
    //             PostOrderMappableContainer<Data>,
    //             InOrderMappableContainer<Data>,
    //             BreadthMappableContainer<Data>,
    //             PreOrderFoldableContainer<Data>,
    //             PostOrderFoldableContainer<Data>,
    //             InOrderFoldableContainer<Data>,
    //             BreadthFoldableContainer<Data>

private:

    // ...

protected:

    // using InOrder/BreadthMappableContainer<Data>::???;

    // ...

public:

    struct Node
    {

    private:

        // ...

    protected:

        // Comparison operators
        bool operator==(const Node&) const noexcept; // Comparison of abstract types is possible, but should not be visible.
        bool operator!=(const Node&) const noexcept; // Comparison of abstract types is possible, but should not be visible.

    public:

        friend class BinaryTree<Data>;

        /* ********************************************************************** */
        Data dato;
        // Destructor
        virtual ~Node() = default;

        /* ********************************************************************** */

        // Copy assignment
        Node& operator=(const Node&) = delete; // Copy assignment of abstract types should not be possible.

        // Move assignment
        Node& operator=(Node&&) noexcept = delete; // Move assignment of abstract types should not be possible.

        /* ********************************************************************** */


        // Specific member functions

        virtual Data& Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)
        virtual const Data& Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

        virtual bool IsLeaf() const noexcept {return !(HasRightChild() || HasLeftChild());}; // (concrete function should not throw exceptions)
        virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
        virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

        virtual Node& LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
        virtual Node& RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

    };

    /* ************************************************************************ */

    // Destructor
        virtual ~BinaryTree() = default;

    /* ************************************************************************ */

    // Copy assignment
    BinaryTree& operator=(const BinaryTree& bt) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    BinaryTree& operator=(BinaryTree&& bt) noexcept = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BinaryTree&) const noexcept; // Comparison of abstract binary tree is possible.
    bool operator!=(const BinaryTree&) const noexcept; // Comparison of abstract binary tree is possible.

    /* ************************************************************************ */

    // Specific member functions

    virtual Node& Root() const = 0; // (concrete function must throw std::length_error when empty)
    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    using typename MappableContainer<Data>::MapFunctor;

    virtual void Map(MapFunctor,void*) override; // Override MappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    using typename FoldableContainer<Data>::FoldFunctor;

    virtual void Fold(FoldFunctor, const void*,void*) const override; // Override FoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PreOrderMappableContainer)

    void MapPreOrder(const MapFunctor, void*) override; // Override PreOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PreOrderFoldableContainer)

    void FoldPreOrder(const FoldFunctor, const void*, void*) const override; // Override PreOrderFoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PostOrderMappableContainer)

    void MapPostOrder(const MapFunctor, void*) override; // Override PostOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PostOrderFoldableContainer)

    void FoldPostOrder(const FoldFunctor, const void*, void*) const override; // Override PostOrderFoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from InOrderMappableContainer)

    void MapInOrder(const MapFunctor, void*) override; // Override InOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from InOrderFoldableContainer)

    void FoldInOrder(const FoldFunctor, const void*, void*) const override; // Override InOrderFoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from BreadthMappableContainer)

    void MapBreadth(const MapFunctor, void*) override; // Override BreadthMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from BreadthFoldableContainer)

    void FoldBreadth(const FoldFunctor, const void*, void*) const override; // Override BreadthFoldableContainer member

protected:

    // Auxiliary member functions (for PreOrderMappableContainer)

    void MapPreOrder(const MapFunctor, void*, Node*); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for PreOrderFoldableContainer)

    void FoldPreOrder(const FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for PostOrderMappableContainer)

    void MapPostOrder(const MapFunctor, void*, Node*); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for PostOrderFoldableContainer)

    void FoldPostOrder(const FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for InOrderMappableContainer)

    void MapInOrder(const MapFunctor, void*, Node*); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for InOrderFoldableContainer)

    void FoldInOrder(const FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for BreadthMappableContainer)

    void MapBreadth(const MapFunctor, void*, Node*); // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for BreadthFoldableContainer)

    void FoldBreadth(const FoldFunctor, const void*, void*, Node*) const; // Accessory function executing from one node of the tree

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator: virtual public ForwardIterator<Data>,
                          virtual public ResettableIterator<Data>
{
    // Must extend ForwardIterator<Data>,
    //             ResettableIterator<Data>

private:

    // ...

protected:
    struct BinaryTree<Data>::Node root = nullptr;
    struct BinaryTree<Data>::Node curr = nullptr;
    Queue<struct BinaryTree<Data>::Node*> queue;
public:

    // Specific constructors
    BTPreOrderIterator(BinaryTree<Data> bt); // An iterator over a given binary tree

    /* ************************************************************************ */

    // Copy constructor
    BTPreOrderIterator(const BTPreOrderIterator& poi);

    // Move constructor
    BTPreOrderIterator(BTPreOrderIterator&& poi) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~BTPreOrderIterator() = default;

    /* ************************************************************************ */

    // Copy assignment
    BTPreOrderIterator& operator=(const BTPreOrderIterator& poi);

    // Move assignment
    BTPreOrderIterator& operator=(BTPreOrderIterator&& poi) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BTPreOrderIterator& poi) const noexcept;
    bool operator!=(const BTPreOrderIterator& poi) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)

    Data& operator*() const; // (throw std::out_of_range when terminated)

    bool Terminated() const noexcept override; // (should not throw exceptions)

    /* ************************************************************************ */

    // Specific member functions (inherited from ForwardIterator)

    BTPreOrderIterator& operator++() override; // (throw std::out_of_range when terminated)

    /* ************************************************************************ */

    // Specific member functions (inherited from ResettableIterator)

    // type Reset() specifiers; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator: virtual public ForwardIterator<Data>,
                           virtual public ResettableIterator<Data>
{
    // Must extend ForwardIterator<Data>,
    //             ResettableIterator<Data>

private:

    // ...

protected:

    // ...

public:

    // Specific constructors
    // BTPostOrderIterator(argument) specifiers; // An iterator over a given binary tree

    /* ************************************************************************ */

    // Copy constructor
    // BTPostOrderIterator(argument) specifiers;

    // Move constructor
    // BTPostOrderIterator(argument) specifiers;

    /* ************************************************************************ */

    // Destructor
    // ~BTPostOrderIterator() specifiers;

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument) specifiers;

    // Move assignment
    // type operator=(argument) specifiers;

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers;
    // type operator!=(argument) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)

    // type operator*() specifiers; // (throw std::out_of_range when terminated)

    // type Terminated() specifiers; // (should not throw exceptions)

    /* ************************************************************************ */

    // Specific member functions (inherited from ForwardIterator)

    // type operator++() specifiers; // (throw std::out_of_range when terminated)

    /* ************************************************************************ */

    // Specific member functions (inherited from ResettableIterator)

    // type Reset() specifiers; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator: virtual public ForwardIterator<Data>,
                         virtual public ResettableIterator<Data>
{
    // Must extend ForwardIterator<Data>,
    //             ResettableIterator<Data>

private:

    // ...

protected:

    // ...

public:

    // Specific constructors
    // BTInOrderIterator(argument) specifiers; // An iterator over a given binary tree

    /* ************************************************************************ */

    // Copy constructor
    // BTInOrderIterator(argument) specifiers;

    // Move constructor
    // BTInOrderIterator(argument) specifiers;

    /* ************************************************************************ */

    // Destructor
    // ~BTInOrderIterator() specifiers;

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument) specifiers;

    // Move assignment
    // type operator=(argument) specifiers;

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers;
    // type operator!=(argument) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)

    // type operator*() specifiers; // (throw std::out_of_range when terminated)

    // type Terminated() specifiers; // (should not throw exceptions)

    /* ************************************************************************ */

    // Specific member functions (inherited from ForwardIterator)

    // type operator++() specifiers; // (throw std::out_of_range when terminated)

    /* ************************************************************************ */

    // Specific member functions (inherited from ResettableIterator)

    // type Reset() specifiers; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator: virtual public ForwardIterator<Data>,
                         virtual public ResettableIterator<Data>
{
    // Must extend ForwardIterator<Data>,
    //             ResettableIterator<Data>

private:

    // ...

protected:

    // ...

public:

    // Specific constructors
    // BTBreadthIterator(argument) specifiers; // An iterator over a given binary tree

    /* ************************************************************************ */

    // Copy constructor
    // BTBreadthIterator(argument) specifiers;

    // Move constructor
    // BTBreadthIterator(argument) specifiers;

    /* ************************************************************************ */

    // Destructor
    // ~BTBreadthIterator() specifiers;

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument) specifiers;

    // Move assignment
    // type operator=(argument) specifiers;

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers;
    // type operator!=(argument) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)

    // type operator*() specifiers; // (throw std::out_of_range when terminated)

    // type Terminated() specifiers; // (should not throw exceptions)

    /* ************************************************************************ */

    // Specific member functions (inherited from ForwardIterator)

    // type operator++() specifiers; // (throw std::out_of_range when terminated)

    /* ************************************************************************ */

    // Specific member functions (inherited from ResettableIterator)

    // type Reset() specifiers; // (should not throw exceptions)

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
