#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

    template<typename Data>
    class BinaryTreeLnk : virtual public BinaryTree<Data>
    {
        // Must extend BinaryTree<Data>

    private:


    protected:

        using BinaryTree<Data>::size;
        // ...

        struct NodeLnk : virtual public BinaryTree<Data>::Node   // Must extend Node
        {

        private:

            // ...

        protected:

            // ...

        public:
            using BinaryTree<Data>::Node::dato;
            NodeLnk *right = nullptr;
            NodeLnk *left = nullptr;

            NodeLnk() = default;

            virtual ~NodeLnk()
            {
                if (HasRightChild())
                    delete right;
                if (HasLeftChild())
                    delete left;
            };

            NodeLnk(const NodeLnk& nl)
            {
                dato = nl.dato;
                if (nl.HasRightChild())
                    right = new NodeLnk(nl.right);
                if (nl.HasLeftChild())
                    left = new NodeLnk(nl.left);
            };

            NodeLnk(NodeLnk&& nl)
            {
                std::swap(dato, nl.dato);
                std::swap(right, nl.right);
                std::swap(left, nl.left);
            };

            NodeLnk(const Data& d)
            {
                dato = d;
            };

            NodeLnk(Data&& d)
            {
                dato = std::move(d);
            }

            bool HasLeftChild() const noexcept override // (concrete function should not throw exceptions)
            {
                return (left != nullptr);
            };

            bool HasRightChild() const noexcept override // (concrete function should not throw exceptions)
            {
                return (right != nullptr);
            };

            NodeLnk& LeftChild() const override // (concrete function must throw std::out_of_range when not existent)
            {
                if (!HasLeftChild())
                    throw std::out_of_range("Out of range!");
                return left;
            };

            NodeLnk& RightChild() const override // (concrete function must throw std::out_of_range when not existent)
            {
                if (!HasRightChild())
                    throw std::out_of_range("Out of range!");
                return right;

            };

        };

        NodeLnk *root = nullptr;
    public:

        // Default constructor
        BinaryTreeLnk() = default;

        /* ************************************************************************ */

        // Specific constructors
        BinaryTreeLnk(LinearContainer<Data>& lc); // A binary tree obtained from a LinearContainer

        /* ************************************************************************ */

        // Copy constructor
        BinaryTreeLnk(const BinaryTreeLnk& btl);

        // Move constructor
        BinaryTreeLnk(BinaryTreeLnk&& btl) noexcept;

        /* ************************************************************************ */

        // Destructor
        virtual ~BinaryTreeLnk();

        /* ************************************************************************ */

        // Copy assignment
        BinaryTreeLnk& operator=(const BinaryTreeLnk& btl);

        // Move assignment
        BinaryTreeLnk& operator=(BinaryTreeLnk&& btl) noexcept;

        /* ************************************************************************ */

        // Specific member functions (inherited from BinaryTree)

        NodeLnk& Root() const override // Override BinaryTree member (throw std::length_error when empty)
        {
            if (size == 0)
                throw std::length_error("Lenght error!");
            return root;
        }

        /* ************************************************************************ */

        // Specific member functions (inherited from Container)

        void Clear() override; // Override Container member

    };

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
