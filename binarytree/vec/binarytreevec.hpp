#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

    template<typename Data>
    class BinaryTreeVec : virtual public BinaryTree<Data>
    {
        // Must extend BinaryTree<Data>

    private:

        // ...

    protected:

        using BinaryTree<Data>::size;

        // ...

        struct NodeVec : virtual public BinaryTree<Data>::Node  // Must extend Node
        {

        private:

            // ...

        protected:

            // ...

        public:

            unsigned long index;
            Vector<NodeVec *>& arrayRef = nullptr;

            NodeVec() = default;

            NodeVec(Vector<Data>& arr);

            Data& Element() noexcept override; // Mutable access to the element (concrete function should not throw exceptions)
            const Data& Element() const noexcept override; // Immutable access to the element (concrete function should not throw exceptions)

            bool HasLeftChild() const noexcept override; // (concrete function should not throw exceptions)
            bool HasRightChild() const noexcept override; // (concrete function should not throw exceptions)

            NodeVec& LeftChild() const override; // (concrete function must throw std::out_of_range when not existent)
            NodeVec& RightChild() const override; // (concrete function must throw std::out_of_range when not existent)
        };

        Vector<NodeVec *> array;
    public:

        // Default constructor
        BinaryTreeVec() = default;

        /* ************************************************************************ */

        // Specific constructors
        BinaryTreeVec(LinearContainer<Data>& lc); // A binary tree obtained from a LinearContainer

        /* ************************************************************************ */

        // Copy constructor
        BinaryTreeVec(const BinaryTreeVec& btv);

        // Move constructor
        BinaryTreeVec(BinaryTreeVec&& btv) noexcept;

        /* ************************************************************************ */

        // Destructor
        virtual ~BinaryTreeVec();

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

        // Specific member functions (inherited from BinaryTree)

        // type Root() specifiers; // Override BinaryTree member (throw std::length_error when empty)

        /* ************************************************************************ */

        // Specific member functions (inherited from Container)

        // type Clear() specifiers; // Override Container member

        /* ************************************************************************ */

        // Specific member functions (inherited from BreadthMappableContainer)

        // type MapBreadth(arguments) specifiers; // Override BreadthMappableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from BreadthFoldableContainer)

        // type FoldBreadth(arguments) specifiers; // Override BreadthFoldableContainer member

    };

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
