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

        virtual const Data& Min() const // (concrete function must throw std::length_error when empty)
        {
            if(size == 0)
                throw std::length_error("Length error!");
            return FindPointerToMin(root)->dato;
        }
        virtual Data MinNRemove() // (concrete function must throw std::length_error when empty)
        {
            if(size == 0)
                throw std::length_error("Length error!");
            return DataNDelete(&FindPointerToMin(root));
        }
        virtual void RemoveMin() // (concrete function must throw std::length_error when empty)
        {
            if(size == 0)
                throw std::length_error("Length error!");
            delete &FindPointerToMin(root);
        }

        virtual const Data& Max() const // (concrete function must throw std::length_error when empty)
        {
            if(size == 0)
                throw std::length_error("Length error!");
            return &FindPointerToMax(root)->dato;
        }
        virtual Data MaxNRemove() // (concrete function must throw std::length_error when empty)
        {
            if(size == 0)
                throw std::length_error("Length error!");
            return DataNDelete(&FindPointerToMax(root));
        }
        virtual void RemoveMax() // (concrete function must throw std::length_error when empty)
        {
            if(size == 0)
                throw std::length_error("Length error!");
            delete &FindPointerToMax(root);
        }

        virtual const Data& Predecessor(const Data& d) const // (concrete function must throw std::length_error when not found)
        {
            NodeLnk* ptr = &FindPointerToPredecessor(root, d);
            if(ptr==nullptr)
                throw std::length_error("Length error!");
            return ptr->dato;
        }
        virtual Data PredecessorNRemove(const Data& d) // (concrete function must throw std::length_error when not found)
        {
            NodeLnk* ptr = &FindPointerToPredecessor(root, d);
            if(ptr==nullptr)
                throw std::length_error("Length error!");
            return DataNDelete(Detach(*ptr));
        }
        virtual void RemovePredecessor(const Data& d) // (concrete function must throw std::length_error when not found)
        {
            NodeLnk* ptr = &FindPointerToPredecessor(root, d);
            if(ptr==nullptr)
                throw std::length_error("Length error!");
            Remove(ptr->dato);
        }

        virtual const Data& Successor(const Data& d) const // (concrete function must throw std::length_error when not found)
        {
            NodeLnk* ptr = &FindPointerToSuccessor(root, d);
            if(ptr==nullptr)
                throw std::length_error("Length error!");
            return ptr->dato;
        }
        virtual Data SuccessorNRemove(const Data& d) // (concrete function must throw std::length_error when not found)
        {
            NodeLnk* ptr = FindPointerToSuccessor(root, d);
            if(ptr==nullptr)
                throw std::length_error("Length error!");
            return DataNDelete(Detach(ptr));
        }
        virtual void RemoveSuccessor(const Data& d) // (concrete function must throw std::length_error when not found)
        {
            NodeLnk* ptr = FindPointerToSuccessor(root, d);
            if(ptr==nullptr)
                throw std::length_error("Length error!");
            Detach(*ptr);
        }

        /* ************************************************************************ */

        // Specific member functions (inherited from DictionaryContainer)

        virtual void Insert(const Data& d) override// Override DictionaryContainer member (Copy of the value)
        {
            // qualcosa?
        }
        virtual void Insert(Data&& d) override // Override DictionaryContainer member (Move of the value)
        {
            // qualcosa?
        }
        virtual void Remove(const Data& d) override // Override DictionaryContainer member
        {
            // qualcosa?
            delete Detach(FindPointerTo(d));
        }

        /* ************************************************************************ */

        // Specific member functions (inherited from TestableContainer)

        virtual bool Exists(const Data& d) const noexcept override // Override TestableContainer member
        {
            return FindPointerTo(root,d) != nullptr;
        }

    protected:

        // Auxiliary member functions

        virtual Data DataNDelete(NodeLnk *n)
        {
            n = Detach(n);
            Data d = std::move(n->dato);
            delete n;
            return d;
        }

        virtual NodeLnk* Detach(NodeLnk *& n) noexcept
        {
            if(n->HasRightChild() && n->HasLeftChild())
                n = DetachMin(n);
            else
            {
                if(n->HasRightChild())
                    n = Skip2Right();
                if(n->HasLeftChild())
                    n = Skip2Left();
            }
            return n;
        }

        virtual NodeLnk* DetachMin(NodeLnk *& n) noexcept
        {
            NodeLnk* ptr = FindPointerToMin(n->right);
            NodeLnk* m = nullptr;
            std::swap(m,ptr);
            std::swap(m,n);
            size--;
            return m;
        }

        virtual NodeLnk* DetachMax(NodeLnk *& n) noexcept
        {
            // qualcosa?
        }

        virtual NodeLnk *Skip2Left(NodeLnk *& n) noexcept
        {
            NodeLnk* l = nullptr;
            if(n != nullptr)
            {
                std::swap(l,n->left);
                std::swap(l,n);
                size--;
            }
            return l;
        }

        virtual NodeLnk *Skip2Right(NodeLnk *& n) noexcept
        {
            NodeLnk* r = nullptr;
            if(n != nullptr)
            {
                std::swap(r,n->right);
                std::swap(r,n);
                size--;
            }
            return r;
        }

        virtual NodeLnk *& FindPointerToMin(NodeLnk *& n) noexcept// Both mutable & unmutable versions
        {
            return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(n));
        }
        virtual NodeLnk *const& FindPointerToMin(NodeLnk *const& n) const noexcept // Both mutable & unmutable versions
        {
            NodeLnk* const* ptr = &n;
            NodeLnk* curr = n;
            if(curr != nullptr)
            {
                while(curr->left != nullptr)
                {
                    ptr = &curr->left;
                    curr = curr->left;
                }
            }
            return *ptr;
        }
        virtual NodeLnk *& FindPointerToMax(NodeLnk *& n) noexcept // Both mutable & unmutable versions
        {
            return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(n));
        }
        virtual NodeLnk *const& FindPointerToMax(NodeLnk *const& n) const noexcept // Both mutable & unmutable versions
        {
            NodeLnk* const* ptr = &n;
            NodeLnk* curr = n;
            if(curr != nullptr)
            {
                while(curr->right != nullptr)
                {
                    ptr = &curr->right;
                    curr = curr->right;
                }
            }
            return *ptr;
        }
        virtual NodeLnk *& FindPointerTo(NodeLnk *& n, const Data& d) noexcept // Both mutable & unmutable versions
        {
            return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerTo(n,d));
        }
        virtual NodeLnk *const& FindPointerTo(NodeLnk *const& n, const Data& d) noexcept // Both mutable & unmutable versions
        {
            NodeLnk* const* ptr = &n;
            NodeLnk* curr = n;
            while(curr != nullptr)
            {
                if(curr->dato < d)
                {
                    ptr = &curr->right;
                    curr = curr->right;
                }
                else
                {
                    if(curr->dato > d)
                    {
                        ptr = &curr->left;
                        curr = curr->left;
                    }
                    else
                        break;
                }
            }
            return *ptr;
        }

        virtual NodeLnk **FindPointerToPredecessor(NodeLnk *& n, const Data& d) noexcept // Both mutable & unmutable versions
        {
            return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(n,d));
        }
        virtual NodeLnk *const *FindPointerToPredecessor(NodeLnk *const& n, const Data& d) const noexcept // Both mutable & unmutable versions
        {
            NodeLnk* const* ptr = &n;
            NodeLnk* const* tmp = nullptr;
            while(true)
            {
                NodeLnk& cur = **ptr;
                if(cur.element < d)
                {
                    tmp = ptr;
                    if(cur.right == nullptr)
                        return tmp;
                    else
                        ptr = &cur.right;
                }
                else
                {
                    if(cur.right == nullptr)
                        return tmp;
                    else
                    {
                        if(cur.element > d)
                            ptr = &cur.left;
                        else
                            return &FindPointerToMax(cur.left);
                    }
                }

            }
        }
        virtual NodeLnk **FindPointerToSuccessor(NodeLnk *& n, const Data& d) noexcept // Both mutable & unmutable versions
        {
            return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(n,d));
        }
        virtual NodeLnk *const *FindPointerToSuccessor(NodeLnk *const& n, const Data& d) const noexcept // Both mutable & unmutable versions
        {
            NodeLnk* const* ptr = &n;
            NodeLnk* const* tmp = nullptr;
            while(true)
            {
                NodeLnk& cur = **ptr;
                if(cur.element > d)
                {
                    tmp = ptr;
                    if(cur.left == nullptr)
                        return tmp;
                    else
                        ptr = &cur.left;
                }
                else
                {
                    if(cur.right == nullptr)
                        return tmp;
                    else
                    {
                        if(cur.element < d)
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
