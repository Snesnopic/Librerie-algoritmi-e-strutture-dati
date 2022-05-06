#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

    template<typename Data>
    class BST : virtual public DictionaryContainer<Data>, virtual public BinaryTreeLnk<Data>
    { // Must extend BinaryTreeLnk<Data>

    private:

        // ...

    protected:

        using typename BinaryTreeLnk<Data>::BinaryTreeLnk::NodeLnk;
        using BinaryTreeLnk<Data>::size;
        using BinaryTreeLnk<Data>::root;

        // ...

    public:

        // Default constructor
        BST() = default;

        /* ************************************************************************ */

        // Specific constructors
        BST(const LinearContainer<Data>& lc); // A bst obtained from a LinearContainer

        /* ************************************************************************ */

        // Copy constructor
        BST(const BST& bst) : BinaryTreeLnk<Data>(bst) {};

        // Move constructor
        BST(BST&& bst) noexcept: BinaryTreeLnk<Data>(std::move(bst)) {};

        /* ************************************************************************ */

        // Destructor
        virtual ~BST() = default;

        /* ************************************************************************ */

        // Copy assignment
        BST& operator=(const BST& bst);

        // Move assignment
        BST& operator=(BST&& bst) noexcept;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const BST& bst) const noexcept;

        bool operator!=(const BST& bst) const noexcept;

        /* ************************************************************************ */

        // Specific member functions

        virtual const Data& Min() const; // (concrete function must throw std::length_error when empty)
        virtual Data MinNRemove(); // (concrete function must throw std::length_error when empty)
        virtual void RemoveMin(); // (concrete function must throw std::length_error when empty)

        virtual const Data& Max() const; // (concrete function must throw std::length_error when empty)
        virtual Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
        virtual void RemoveMax(); // (concrete function must throw std::length_error when empty)

        virtual const Data& Predecessor(const Data& d) const; // (concrete function must throw std::length_error when not found)
        virtual Data PredecessorNRemove(const Data& d); // (concrete function must throw std::length_error when not found)
        virtual void RemovePredecessor(const Data& d); // (concrete function must throw std::length_error when not found)

        virtual const Data& Successor(const Data& d) const; // (concrete function must throw std::length_error when not found)
        virtual Data SuccessorNRemove(const Data& d); // (concrete function must throw std::length_error when not found)
        virtual void RemoveSuccessor(const Data& d); // (concrete function must throw std::length_error when not found)

        /* ************************************************************************ */

        // Specific member functions (inherited from DictionaryContainer)

        virtual void Insert(const Data& d) override; // Override DictionaryContainer member (Copy of the value)
        virtual void Insert(Data&& d) override; // Override DictionaryContainer member (Move of the value)
        virtual void Remove(const Data& d) override; // Override DictionaryContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from TestableContainer)

        virtual bool Exists(const Data& d) const noexcept override; // Override TestableContainer member

    protected:

        // Auxiliary member functions

        virtual Data DataNDelete(NodeLnk *n);

        virtual NodeLnk *Detach(NodeLnk) noexcept;

        virtual NodeLnk *DetachMin(NodeLnk *& n) noexcept;

        virtual NodeLnk *DetachMax(NodeLnk *& n) noexcept;

        virtual NodeLnk *Skip2Left(NodeLnk *& n) noexcept;

        virtual NodeLnk *Skip2Right(NodeLnk *& n) noexcept;

        virtual NodeLnk *& FindPointerToMin(NodeLnk *& n) noexcept; // Both mutable & unmutable versions
        virtual NodeLnk *const& FindPointerToMin(NodeLnk *const& n) const noexcept; // Both mutable & unmutable versions
        virtual NodeLnk *& FindPointerToMax(NodeLnk *& n) noexcept; // Both mutable & unmutable versions
        virtual NodeLnk *const& FindPointerToMax(NodeLnk *const& n) const noexcept; // Both mutable & unmutable versions

        virtual NodeLnk *& FindPointerTo(NodeLnk *& n, const Data&) noexcept; // Both mutable & unmutable versions
        virtual NodeLnk *const& FindPointerTo(NodeLnk *const& n, const Data&) noexcept; // Both mutable & unmutable versions

        virtual NodeLnk **FindPointerToPredecessor(NodeLnk *& n, const Data&) noexcept; // Both mutable & unmutable versions
        virtual NodeLnk *const *FindPointerToPredecessor(NodeLnk *const& n, const Data&) const noexcept; // Both mutable & unmutable versions
        virtual NodeLnk **FindPointerToSuccessor(NodeLnk *& n, const Data&) noexcept; // Both mutable & unmutable versions
        virtual NodeLnk *const *FindPointerToSuccessor(NodeLnk *const& n, const Data&) const noexcept; // Both mutable & unmutable versions

    };

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
