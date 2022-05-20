#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../iterator/iterator.hpp"
#include "../stack/stack.hpp"
#include "../queue/queue.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/lst/queuelst.hpp"


/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

    template<typename Data>
    class BinaryTree
            : virtual public PreOrderMappableContainer<Data>,
              virtual public PostOrderMappableContainer<Data>,
              virtual public InOrderMappableContainer<Data>,
              virtual public BreadthMappableContainer<Data>,
              virtual public PreOrderFoldableContainer<Data>,
              virtual public PostOrderFoldableContainer<Data>,
              virtual public InOrderFoldableContainer<Data>,
              virtual public BreadthFoldableContainer<Data> {
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

        using BreadthMappableContainer<Data>::size;

        // ...

    public:

        struct Node {

        private:

            // ...

        protected:

            // Comparison operators
            bool operator==(
                    const Node &n) const noexcept; // Comparison of abstract types is possible, but should not be visible.
            bool operator!=(
                    const Node &n) const noexcept; // Comparison of abstract types is possible, but should not be visible.

        public:

            friend class BinaryTree<Data>;

            /* ********************************************************************** */
            Data dato{};

            // Destructor
            virtual ~Node() = default;

            /* ********************************************************************** */

            // Copy assignment
            Node &operator=(const Node &n) = delete; // Copy assignment of abstract types should not be possible.

            // Move assignment
            Node &operator=(Node &&n) noexcept = delete; // Move assignment of abstract types should not be possible.

            /* ********************************************************************** */


            // Specific member functions

            Data &Element() noexcept // Mutable access to the element (concrete function should not throw exceptions)
            {
                return dato;
            };

            const Data &
            Element() const noexcept // Immutable access to the element (concrete function should not throw exceptions)
            {
                return dato;
            };

            bool IsLeaf() const noexcept // (concrete function should not throw exceptions)
            {
                return !(HasRightChild() || HasLeftChild());
            };

            virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
            virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

            virtual Node &LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
            virtual Node &RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

        };

        /* ************************************************************************ */

        // Destructor
        virtual ~BinaryTree() = default;

        /* ************************************************************************ */

        // Copy assignment
        BinaryTree &
        operator=(const BinaryTree &bt) = delete; // Copy assignment of abstract types should not be possible.

        // Move assignment
        BinaryTree &
        operator=(BinaryTree &&bt) noexcept = delete; // Move assignment of abstract types should not be possible.

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const BinaryTree &bt) const noexcept; // Comparison of abstract binary tree is possible.
        bool operator!=(const BinaryTree &bt) const noexcept; // Comparison of abstract binary tree is possible.

        /* ************************************************************************ */

        // Specific member functions

        virtual Node &Root() const = 0; // (concrete function must throw std::length_error when empty)
        /* ************************************************************************ */

        // Specific member functions (inherited from MappableContainer)

        using typename MappableContainer<Data>::MapFunctor;

        void Map(MapFunctor f, void *par) override; // Override MappableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from FoldableContainer)

        using typename FoldableContainer<Data>::FoldFunctor;

        void Fold(FoldFunctor f, const void *par, void *acc) const override; // Override FoldableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from PreOrderMappableContainer)

        void MapPreOrder(MapFunctor f, void *par) override; // Override PreOrderMappableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from PreOrderFoldableContainer)

        void FoldPreOrder(FoldFunctor f, const void *par,
                          void *acc) const override; // Override PreOrderFoldableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from PostOrderMappableContainer)

        void MapPostOrder(MapFunctor f, void *par) override; // Override PostOrderMappableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from PostOrderFoldableContainer)

        void FoldPostOrder(FoldFunctor f, const void *par,
                           void *acc) const override; // Override PostOrderFoldableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from InOrderMappableContainer)

        void MapInOrder(MapFunctor f, void *par) override; // Override InOrderMappableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from InOrderFoldableContainer)

        void FoldInOrder(FoldFunctor f, const void *par,
                         void *acc) const override; // Override InOrderFoldableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from BreadthMappableContainer)

        void MapBreadth(MapFunctor f, void *par) override; // Override BreadthMappableContainer member

        /* ************************************************************************ */

        // Specific member functions (inherited from BreadthFoldableContainer)

        void FoldBreadth(FoldFunctor f, const void *par,
                         void *acc) const override; // Override BreadthFoldableContainer member

    protected:

        // Auxiliary member functions (for PreOrderMappableContainer)

        void MapPreOrder(MapFunctor f, void *par, Node *n); // Accessory function executing from one node of the tree

        /* ************************************************************************ */

        // Auxiliary member functions (for PreOrderFoldableContainer)

        void FoldPreOrder(FoldFunctor f, const void *par, void *acc,
                          Node *n) const; // Accessory function executing from one node of the tree

        /* ************************************************************************ */

        // Auxiliary member functions (for PostOrderMappableContainer)

        void MapPostOrder(MapFunctor f, void *par, Node *n); // Accessory function executing from one node of the tree

        /* ************************************************************************ */

        // Auxiliary member functions (for PostOrderFoldableContainer)

        void FoldPostOrder(FoldFunctor f, const void *par, void *acc,
                           Node *n) const; // Accessory function executing from one node of the tree

        /* ************************************************************************ */

        // Auxiliary member functions (for InOrderMappableContainer)

        void MapInOrder(MapFunctor f, void *par, Node *n); // Accessory function executing from one node of the tree

        /* ************************************************************************ */

        // Auxiliary member functions (for InOrderFoldableContainer)

        void FoldInOrder(FoldFunctor f, const void *par, void *acc,
                         Node *n) const; // Accessory function executing from one node of the tree

    };

/* ************************************************************************** */

    template<typename Data>
    class BTPreOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {
        // Must extend ForwardIterator<Data>,
        //             ResettableIterator<Data>

    private:

        // ...

    protected:
        struct BinaryTree<Data>::Node *curr = nullptr;
        StackLst<struct BinaryTree<Data>::Node *> stack{};
        const BinaryTree<Data> *treePtr = nullptr;
    public:

        // Specific constructors
        BTPreOrderIterator(const BinaryTree<Data> &bt); // An iterator over a given binary tree


        /* ************************************************************************ */

        // Copy constructor
        BTPreOrderIterator(const BTPreOrderIterator &poi) {
            curr = poi.curr;
            stack = poi.stack;
            treePtr = poi.treePtr;
        }

        // Move constructor
        BTPreOrderIterator(BTPreOrderIterator &&poi) noexcept {
            std::swap(curr, poi.curr);
            std::swap(stack, poi.stack);
            std::swap(treePtr, poi.treePtr);
        }

        /* ************************************************************************ */

        // Destructor
        virtual ~BTPreOrderIterator() {
            stack.Clear();
        }

        /* ************************************************************************ */

        // Copy assignment
        BTPreOrderIterator &operator=(const BTPreOrderIterator &poi) {
            if (this != &poi) {
                curr = poi.curr;
                stack = poi.stack;
                treePtr = poi.treePtr;
            }
            return *this;
        }

        // Move assignment
        BTPreOrderIterator &operator=(BTPreOrderIterator &&poi) noexcept {
            if (this != &poi) {
                std::swap(curr, poi.curr);
                std::swap(stack, poi.stack);
                std::swap(treePtr, poi.treePtr);
            }
            return *this;
        }

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const BTPreOrderIterator &poi) const noexcept {
            return curr == poi.curr;
        }

        bool operator!=(const BTPreOrderIterator &poi) const noexcept {
            return !(*this == poi);
        }

        /* ************************************************************************ */

        // Specific member functions (inherited from Iterator)

        Data &operator*() const override // (throw std::out_of_range when terminated)
        {
            if (Terminated())
                throw std::out_of_range("Out of range!");
            return curr->dato;
        }

        bool Terminated() const noexcept override // (should not throw exceptions)
        {
            return curr == nullptr;
        }

        /* ************************************************************************ */

        // Specific member functions (inherited from ForwardIterator)

        BTPreOrderIterator &operator++() override; // (throw std::out_of_range when terminated)


        /* ************************************************************************ */

        // Specific member functions (inherited from ResettableIterator)

        void Reset() noexcept override // (should not throw exceptions)
        {
            if (treePtr != nullptr)
                curr = &treePtr->Root();
            stack.Clear();
        }

    };

/* ************************************************************************** */

    template<typename Data>
    class BTPostOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {
        // Must extend ForwardIterator<Data>,
        //             ResettableIterator<Data>

    private:

        // ...

    protected:

        struct BinaryTree<Data>::Node *curr = nullptr;
        StackLst<struct BinaryTree<Data>::Node *> stack{};
        const BinaryTree<Data> *treePtr = nullptr;

        struct BinaryTree<Data>::Node *minLeaf(struct BinaryTree<Data>::Node *n);


    public:

        // Specific constructors
        BTPostOrderIterator(const BinaryTree<Data> &bt); // An iterator over a given binary tree


        /* ************************************************************************ */

        // Copy constructor
        BTPostOrderIterator(const BTPostOrderIterator &poi) {
            curr = poi.curr;
            stack = poi.stack;
            treePtr = poi.treePtr;
        }

        // Move constructor
        BTPostOrderIterator(BTPostOrderIterator &&poi) noexcept {
            std::swap(curr, poi.curr);
            std::swap(stack, poi.stack);
            std::swap(treePtr, poi.treePtr);
        }

        /* ************************************************************************ */

        // Destructor
        virtual ~BTPostOrderIterator() {
            stack.Clear();
        }

        /* ************************************************************************ */

        // Copy assignment
        BTPostOrderIterator &operator=(const BTPostOrderIterator &poi) {
            if (this != &poi) {
                curr = poi.curr;
                stack = poi.stack;
                treePtr = poi.treePtr;
            }
            return *this;
        }

        // Move assignment
        BTPostOrderIterator &operator=(BTPostOrderIterator &&poi) noexcept {
            if (this != &poi) {
                std::swap(curr, poi.curr);
                std::swap(stack, poi.stack);
                std::swap(treePtr, poi.treePtr);
            }
            return *this;
        }

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const BTPostOrderIterator &poi) const noexcept {
            if (curr == poi.curr && stack == poi.stack && treePtr == poi.treePtr)
                return true;
            else
                return false;
        }

        bool operator!=(const BTPostOrderIterator &poi) const noexcept {
            return !(*this == poi);
        }

        /* ************************************************************************ */

        // Specific member functions (inherited from Iterator)

        Data &operator*() const override // (throw std::out_of_range when terminated)
        {
            if (Terminated())
                throw std::out_of_range("Out of range!");
            return curr->dato;
        }

        bool Terminated() const noexcept override // (should not throw exceptions)
        {
            return curr == nullptr;
        }
        /* ************************************************************************ */
        // Specific member functions (inherited from ForwardIterator)

        BTPostOrderIterator &operator++() override; // (throw std::out_of_range when terminated)

        /* ************************************************************************ */

        // Specific member functions (inherited from ResettableIterator)

        void Reset() noexcept override // (should not throw exceptions)
        {
            stack.Clear();
            if (treePtr != nullptr)
                curr = minLeaf(&treePtr->Root());
        }

    };

/* ************************************************************************** */

    template<typename Data>
    class BTInOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {
        // Must extend ForwardIterator<Data>,
        //             ResettableIterator<Data>

    private:

        struct BinaryTree<Data>::Node *curr = nullptr;
        StackLst<struct BinaryTree<Data>::Node *> stack{};
        const BinaryTree<Data> *treePtr = nullptr;

    protected:

        struct BinaryTree<Data>::Node *min(struct BinaryTree<Data>::Node *n);


    public:

        // Specific constructors
        BTInOrderIterator(const BinaryTree<Data> &bt); // An iterator over a given binary tree


        /* ************************************************************************ */

        // Copy constructor
        BTInOrderIterator(const BTInOrderIterator &ii) {
            curr = ii.curr;
            stack = ii.stack;
            treePtr = ii.treePtr;
        }

        // Move constructor
        BTInOrderIterator(BTInOrderIterator &&ii) noexcept {
            std::swap(curr, ii.curr);
            std::swap(stack, ii.stack);
            std::swap(treePtr, ii.treePtr);
        }

        /* ************************************************************************ */

        // Destructor
        virtual ~BTInOrderIterator() {
            stack.Clear();
        }

        /* ************************************************************************ */

        // Copy assignment
        BTInOrderIterator &operator=(const BTInOrderIterator &ii) {
            if (this != &ii) {
                curr = ii.curr;
                stack = ii.stack;
                treePtr = ii.treePtr;
            }
            return *this;
        }

        // Move assignment
        BTInOrderIterator &operator=(BTInOrderIterator &&ii) noexcept {
            if (this != &ii) {
                std::swap(curr, ii.curr);
                std::swap(stack, ii.stack);
                std::swap(treePtr, ii.treePtr);
            }
            return *this;
        }

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const BTInOrderIterator &ii) const noexcept {
            if (curr == ii.curr && stack == ii.stack && treePtr == ii.treePtr)
                return true;
            else
                return false;
        }

        bool operator!=(const BTInOrderIterator &ii) const noexcept {
            return !(*this == ii);
        }

        /* ************************************************************************ */

        // Specific member functions (inherited from Iterator)

        Data &operator*() const override // (throw std::out_of_range when terminated)
        {
            if (Terminated())
                throw std::out_of_range("Out of range!");
            return curr->dato;
        }

        bool Terminated() const noexcept override // (should not throw exceptions)
        {
            return curr == nullptr;
        }
        /* ************************************************************************ */
        // Specific member functions (inherited from ForwardIterator)

        BTInOrderIterator &operator++() override; // (throw std::out_of_range when terminated)

        /* ************************************************************************ */

        // Specific member functions (inherited from ResettableIterator)

        void Reset() noexcept override // (should not throw exceptions)
        {
            stack.Clear();
            if (treePtr != nullptr)
                curr = min(&treePtr->Root());
        }

    };

/* ************************************************************************** */

    template<typename Data>
    class BTBreadthIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {
        // Must extend ForwardIterator<Data>,
        //             ResettableIterator<Data>

    private:

        // ...

    protected:

        struct BinaryTree<Data>::Node *curr = nullptr;
        QueueLst<struct BinaryTree<Data>::Node *> que{};
        const BinaryTree<Data> *treePtr = nullptr;
    public:

        // Specific constructors
        BTBreadthIterator(const BinaryTree<Data> &bt); // An iterator over a given binary tree


        /* ************************************************************************ */

        // Copy constructor
        BTBreadthIterator(const BTBreadthIterator &bi) {
            treePtr = bi.treePtr;
            curr = bi.curr;
            que = bi.que;
        }

        // Move constructor
        BTBreadthIterator(BTBreadthIterator &&bi) noexcept {
            std::swap(treePtr, bi.treePtr);
            std::swap(curr, bi.curr);
            std::swap(que, bi.que);
        }

        /* ************************************************************************ */

        // Destructor
        virtual ~BTBreadthIterator() {
            que.Clear();
        }

        /* ************************************************************************ */

        // Copy assignment
        BTBreadthIterator &operator=(const BTBreadthIterator &bi) {
            if (this != &bi) {
                treePtr = bi.treePtr;
                curr = bi.curr;
                que = bi.que;
            }
            return *this;
        }

        // Move assignment
        BTBreadthIterator &operator=(BTBreadthIterator &&bi) noexcept {
            if (this != &bi) {
                std::swap(treePtr, bi.treePtr);
                std::swap(curr, bi.curr);
                std::swap(que, bi.que);
            }
            return *this;
        }

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const BTBreadthIterator &bi) const noexcept {
            if (treePtr == bi.treePtr && curr == bi.curr && que == bi.que)
                return true;
            else
                return false;
        }

        bool operator!=(const BTBreadthIterator &bi) const noexcept {
            return !(*this == bi);
        }

        /* ************************************************************************ */

        // Specific member functions (inherited from Iterator)

        Data &operator*() const override // (throw std::out_of_range when terminated)
        {
            if (Terminated())
                throw std::out_of_range("Out of range!");
            else
                return curr->dato;
        }

        bool Terminated() const noexcept override // (should not throw exceptions)
        {
            return curr == nullptr;
        }

        /* ************************************************************************ */

        // Specific member functions (inherited from ForwardIterator)

        BTBreadthIterator &operator++() override; // (throw std::out_of_range when terminated)


        /* ************************************************************************ */

        // Specific member functions (inherited from ResettableIterator)

        void Reset() noexcept override // (should not throw exceptions)
        {
            if (treePtr != nullptr)
                curr = &treePtr->Root();
            que.Clear();

        }

    };

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
