#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk: virtual public BinaryTree<Data>
{
    // Must extend BinaryTree<Data>

private:

    // ...

protected:

    using BinaryTree<Data>::size;
    // ...

    struct NodeLnk: virtual public BinaryTree<Data>::Node   // Must extend Node
    {

    private:

        // ...

    protected:

        // ...

    public:

        NodeLnk* right = nullptr;
        NodeLnk* left = nullptr;

    };

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

    // Comparison operators
    // type operator==(argument) specifiers;
    // type operator!=(argument) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from BinaryTree)

    NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
