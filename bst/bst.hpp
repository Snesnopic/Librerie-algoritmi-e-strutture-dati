#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */
#include <iostream>
#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    class BST
            : virtual public DictionaryContainer<Data>,
              virtual public BinaryTreeLnk<Data> { // Must extend BinaryTreeLnk<Data>

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
        BST(const LinearContainer<Data> &lc); // A bst obtained from a LinearContainer

        /* ************************************************************************ */

        // Copy constructor
        BST(const BST &bst) : BinaryTreeLnk<Data>(bst) {};

        // Move constructor
        BST(BST &&bst) noexcept: BinaryTreeLnk<Data>(std::move(bst)) {};

        /* ************************************************************************ */

        // Destructor
        virtual ~BST() = default;

        /* ************************************************************************ */

        // Copy assignment
        BST &operator=(const BST &bst);

        // Move assignment
        BST &operator=(BST &&bst) noexcept;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const BST &bst) const noexcept;

        bool operator!=(const BST &bst) const noexcept;

        /* ************************************************************************ */

        // Specific member functions

        virtual const Data &Min() const // (concrete function must throw std::length_error when empty)
        {
            if (size == 0)
                throw std::length_error("Length error!");
            return FindPointerToMin(root)->dato;
        }

        virtual Data MinNRemove() // (concrete function must throw std::length_error when empty)
        {
            if (size == 0)
                throw std::length_error("Length error!");
            NodeLnk *ptr = DetachMin(root);
            return DataNDelete(ptr);
        }

        virtual void RemoveMin() // (concrete function must throw std::length_error when empty)
        {

            if (size == 0)
                throw std::length_error("Length error!");
            NodeLnk *ptr = DetachMin(root);
            delete ptr;
        }

        virtual const Data &Max() const // (concrete function must throw std::length_error when empty)
        {
            if (size == 0)
                throw std::length_error("Length error!");
            return FindPointerToMax(root)->dato;
        }

        virtual Data MaxNRemove() // (concrete function must throw std::length_error when empty)
        {
            if (size == 0)
                throw std::length_error("Length error!");
            NodeLnk *ptr = DetachMax(root);
            return DataNDelete(ptr);
        }

        virtual void RemoveMax() // (concrete function must throw std::length_error when empty)
        {
            if (size == 0)
                throw std::length_error("Length error!");
            NodeLnk *ptr = DetachMax(root);
            delete ptr;
        }

        virtual const Data &
        Predecessor(const Data &d) const // (concrete function must throw std::length_error when not found)
        {
            NodeLnk *ptr = *FindPointerToPredecessor(root, d);
            if (ptr == nullptr)
                throw std::length_error("Length error!");
            return ptr->dato;
        }

        virtual Data
        PredecessorNRemove(const Data &d) // (concrete function must throw std::length_error when not found)
        {
            NodeLnk *ptr = nullptr;
            std::swap(ptr, *FindPointerToPredecessor(root, d));
            if (ptr == nullptr)
                throw std::length_error("Length error!");
            return DataNDelete(Detach(ptr));
        }

        virtual void RemovePredecessor(const Data &d) // (concrete function must throw std::length_error when not found)
        {
            NodeLnk *ptr = nullptr;
            std::swap(ptr, *FindPointerToPredecessor(root, d));
            if (ptr == nullptr)
                throw std::length_error("Length error!");
            delete Detach(ptr);
        }

        virtual const Data &
        Successor(const Data &d) const // (concrete function must throw std::length_error when not found)
        {
            NodeLnk *ptr = *FindPointerToSuccessor(root, d);
            if (ptr == nullptr)
                throw std::length_error("Length error!");
            return ptr->dato;
        }

        virtual Data SuccessorNRemove(const Data &d) // (concrete function must throw std::length_error when not found)
        {
            NodeLnk *ptr = nullptr;
            std::swap(ptr, *FindPointerToSuccessor(root, d));
            if (ptr == nullptr)
                throw std::length_error("Length error!");
            return DataNDelete(Detach(ptr));
        }

        virtual void RemoveSuccessor(const Data &d) // (concrete function must throw std::length_error when not found)
        {
            NodeLnk *ptr = nullptr;
            std::swap(ptr, *FindPointerToSuccessor(root, d));
            if (ptr == nullptr)
                throw std::length_error("Length error!");
            delete Detach(ptr);
        }

        /* ************************************************************************ */

        // Specific member functions (inherited from DictionaryContainer)

        virtual bool Insert(const Data &d) override// Override DictionaryContainer member (Copy of the value)
        {
            NodeLnk *&ptr = FindPointerTo(root, d);
            if (ptr == nullptr) {
                size++;
                ptr = new NodeLnk(d);
                return true;
            }
            return false;
        }

        virtual bool Insert(Data &&d) override // Override DictionaryContainer member (Move of the value)
        {
            NodeLnk *&ptr = FindPointerTo(root, d);
            if (ptr == nullptr) {
                size++;
                ptr = new NodeLnk(std::move(d));
                return true;
            }
            return false;
        }

        virtual bool Remove(const Data &d) override // Override DictionaryContainer member
        {
            NodeLnk *&ptr = FindPointerTo(root, d);
            if (ptr != nullptr) {
                delete Detach(ptr);
                return true;
            }
            return false;
        }

        /* ************************************************************************ */

        // Specific member functions (inherited from TestableContainer)

        virtual bool Exists(const Data &d) const noexcept override // Override TestableContainer member
        {
            return FindPointerTo(root, d) != nullptr;
        }

    protected:

        // Auxiliary member functions

        virtual Data DataNDelete(NodeLnk *n) {
            Data d = n->dato;
            delete n;
            return d;
        }

        virtual NodeLnk *Detach(NodeLnk *&n) noexcept {
            if (n != nullptr) {
                if (n == root) {
                    NodeLnk *&ptr = *FindPointerToPredecessor(root, n->dato);
                    if (ptr != nullptr) {
                        std::swap(n->dato, ptr->dato);
                        return Detach(ptr);
                    }
                    return nullptr;
                }
                if (n->HasRightChild() && n->HasLeftChild()) {
                    return DetachMin(n->right);
                } else {
                    if (n->HasRightChild())
                        return Skip2Right(n);
                    if (n->HasLeftChild())
                        return Skip2Left(n);
                    size--;
                    NodeLnk *t = new NodeLnk(n->dato);
                    delete n;
                    n = nullptr;
                    return t;
                }
            }
            return nullptr;
        }

        virtual NodeLnk *DetachMin(NodeLnk *&n) noexcept {
            return Skip2Right(FindPointerToMin(n));
        }

        virtual NodeLnk *DetachMax(NodeLnk *&n) noexcept {
            return Skip2Left(FindPointerToMax(n));
        }

        virtual NodeLnk *Skip2Left(NodeLnk *&n) noexcept {
            NodeLnk *l = nullptr;
            if (n != nullptr) {
                std::swap(l, n->left);
                std::swap(l, n);
                size--;
            }
            return l;
        }

        virtual NodeLnk *Skip2Right(NodeLnk *&n) noexcept {
            NodeLnk *r = nullptr;
            if (n != nullptr) {
                std::swap(r, n->right);
                std::swap(r, n);
                size--;
            }
            return r;
        }

        virtual NodeLnk *&FindPointerToMin(NodeLnk *&n) noexcept// Both mutable & unmutable versions
        {
            return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(n));
        }

        virtual NodeLnk *const &FindPointerToMin(NodeLnk *const &n) const noexcept // Both mutable & unmutable versions
        {
            NodeLnk *const *ptr = &n;
            NodeLnk *curr = n;
            if (curr != nullptr) {
                while (curr->left != nullptr) {
                    ptr = &curr->left;
                    curr = curr->left;
                }
            }
            return *ptr;
        }

        virtual NodeLnk *&FindPointerToMax(NodeLnk *&n) noexcept // Both mutable & unmutable versions
        {
            return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(n));
        }

        virtual NodeLnk *const &FindPointerToMax(NodeLnk *const &n) const noexcept // Both mutable & unmutable versions
        {
            NodeLnk *const *ptr = &n;
            NodeLnk *curr = n;
            if (curr != nullptr) {
                while (curr->right != nullptr) {
                    ptr = &curr->right;
                    curr = curr->right;
                }
            }
            return *ptr;
        }

        virtual NodeLnk *&FindPointerTo(NodeLnk *&n, const Data &d) noexcept // Both mutable & unmutable versions
        {
            return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerTo(n, d));
        }

        virtual NodeLnk *const &
        FindPointerTo(NodeLnk *const &n, const Data &d) const noexcept // Both mutable & unmutable versions
        {
            NodeLnk *const *ptr = &n;
            NodeLnk *curr = n;
            while (curr != nullptr) {
                if (curr->dato < d) {
                    ptr = &curr->right;
                    curr = curr->right;
                } else {
                    if (curr->dato > d) {
                        ptr = &curr->left;
                        curr = curr->left;
                    } else
                        break;
                }
            }
            return *ptr;
        }

        virtual NodeLnk **
        FindPointerToPredecessor(NodeLnk *&n, const Data &d) noexcept // Both mutable & unmutable versions
        {
            return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(n, d));
        }

        virtual NodeLnk *const *
        FindPointerToPredecessor(NodeLnk *const &n, const Data &d) const noexcept // Both mutable & unmutable versions
        {
            NodeLnk *const *ptr = &n;
            NodeLnk *const *tmp = nullptr;
            while (true) {
                NodeLnk &cur = **ptr;
                if (cur.dato < d) {
                    tmp = ptr;
                    if (cur.right == nullptr || cur.right->dato == d)
                        return tmp;
                    else
                        ptr = &cur.right;
                } else {
                    if (cur.left == nullptr)
                        return tmp;
                    else {
                        if (cur.dato > d)
                            ptr = &cur.left;
                        else
                            return &FindPointerToMax(cur.left);
                    }
                }
            }
        }

        virtual NodeLnk **
        FindPointerToSuccessor(NodeLnk *&n, const Data &d) noexcept // Both mutable & unmutable versions
        {
            return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(n, d));
        }

        virtual NodeLnk *const *
        FindPointerToSuccessor(NodeLnk *const &n, const Data &d) const noexcept // Both mutable & unmutable versions
        {
            NodeLnk *const *ptr = &n;
            NodeLnk *const *tmp = nullptr;
            while (true) {
                NodeLnk &cur = **ptr;
                if (cur.dato > d) {
                    tmp = ptr;
                    if (cur.left == nullptr || cur.left->dato == d)
                        return tmp;
                    else
                        ptr = &cur.left;
                } else {
                    if (cur.right == nullptr)
                        return tmp;
                    else {
                        if (cur.dato < d)
                            ptr = &cur.right;
                        else
                            return &FindPointerToMin(cur.right);
                    }
                }
            }
        }
    };

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
