// #include "..."

namespace lasd
{

/* ************************************************************************** */
    template<typename Data>
    bool BinaryTree<Data>::Node::operator==(const Node& n) const noexcept
    {
        if (this == nullptr && n == nullptr)
            return true;
        return ((dato == n.dato) && (RightChild() == n.RightChild()) && (LeftChild() == n.LeftChild()));
    }

    template<typename Data>
    bool BinaryTree<Data>::Node::operator!=(const Node& n) const noexcept
    {
        return !(*this == n);
    }

    template<typename Data>
    bool BinaryTree<Data>::operator==(const BinaryTree& bt) const noexcept
    {
        if (size == bt.size)
            return Root() == bt.Root();
        return false;
    }

    template<typename Data>
    bool BinaryTree<Data>::operator!=(const BinaryTree& bt) const noexcept
    {
        return !(*this == bt);
    }

    template<typename Data>
    void BinaryTree<Data>::Map(MapFunctor f, void *par)  // Override MappableContainer member
    {
        MapPreOrder(f, par, Root());
    }

    template<typename Data>
    void BinaryTree<Data>::Fold(FoldFunctor f, const void *par, void *acc) const  // Override FoldableContainer member
    {
        FoldPreOrder(f, par, acc, Root());
    }

    template<typename Data>
    void BinaryTree<Data>::MapPreOrder(MapFunctor f, void *par)  // Override PreOrderMappableContainer member
    {
        if (Root() != nullptr)
            MapPreOrder(f, par, Root());
    }

    template<typename Data>
    void BinaryTree<Data>::FoldPreOrder(FoldFunctor f, const void *par, void *acc) const  // Override PreOrderFoldableContainer member
    {
        if (Root() != nullptr)
            FoldPreOrder(f, par, acc, Root());
    }

    template<typename Data>
    void BinaryTree<Data>::MapPostOrder(MapFunctor f, void *par) // Override PostOrderMappableContainer member
    {
        if (Root() != nullptr)
            MapPostOrder(f, par, Root());
    }

    template<typename Data>
    void BinaryTree<Data>::FoldPostOrder(FoldFunctor f, const void *par, void *acc) const // Override PostOrderFoldableContainer member
    {
        if (Root() != nullptr)
            FoldPostOrder(f, par, acc, Root());
    }

    template<typename Data>
    void BinaryTree<Data>::MapInOrder(MapFunctor f, void *par) // Override InOrderMappableContainer member
    {
        if (Root() != nullptr)
            MapInOrder(f, par, Root());
    }

    template<typename Data>
    void BinaryTree<Data>::FoldInOrder(FoldFunctor f, const void *par, void *acc) const // Override InOrderFoldableContainer member
    {
        if (Root() != nullptr)
            FoldInOrder(f, par, acc, Root());
    }

    template<typename Data>
    void BinaryTree<Data>::MapBreadth(MapFunctor f, void *par) // Override BreadthMappableContainer member
    {
        if (Root() != nullptr)
        {
            Queue<Node *> queue;
            queue.Enqueue(Root());
            Node *n = nullptr;
            while (!queue.Empty())
            {
                n = queue.Head();
                f(n->dato, par);
                queue.Dequeue();
                if (n->HasLeftChild())
                    queue.Enqueue(n->LeftChild());
                if (n->HasRightChild())
                    queue.Enqueue(n->RightChild());
            }
        }
    }

    template<typename Data>
    void BinaryTree<Data>::FoldBreadth(FoldFunctor f, const void *par, void *acc) const  // Override BreadthFoldableContainer member
    {
        if (Root() != nullptr)
        {
            Queue<Node *> queue;
            queue.Enqueue(Root());
            Node *n = nullptr;
            while (!queue.Empty())
            {
                n = queue.Head();
                f(n->dato, par, acc);
                queue.Dequeue();
                if (n->HasLeftChild())
                    queue.Enqueue(n->LeftChild());
                if (n->HasRightChild())
                    queue.Enqueue(n->RightChild());
            }
        }
    }


    template<typename Data>
    void BinaryTree<Data>::MapPreOrder(MapFunctor f, void *par, Node *n) // Accessory function executing from one node of the tree
    {
        f(n->dato, par);
        if (n->HasLeftChild())
            MapPreOrder(f, par, n->LeftChild());
        if (n->HasRightChild())
            MapPreOrder(f, par, n->RightChild());
    }

    template<typename Data>
    void BinaryTree<Data>::FoldPreOrder(FoldFunctor f, const void *par, void *acc, Node *n) const // Accessory function executing from one node of the tree
    {
        f(n->dato, par, acc);
        if (n->HasLeftChild())
            FoldPreOrder(f, par, n->LeftChild());
        if (n->HasRightChild())
            FoldPreOrder(f, par, n->RightChild());
    }

    template<typename Data>
    void BinaryTree<Data>::MapPostOrder(MapFunctor f, void *par, Node *n) // Accessory function executing from one node of the tree
    {
        if (n->HasLeftChild())
            MapPostOrder(f, par, n->LeftChild());
        if (n->HasRightChild())
            MapPostOrder(f, par, n->RightChild());
        f(n->dato, par);
    }

    template<typename Data>
    void BinaryTree<Data>::FoldPostOrder(FoldFunctor f, const void *par, void *acc, Node *n) const // Accessory function executing from one node of the tree
    {
        if (n->HasLeftChild())
            FoldPostOrder(f, par, acc, n->LeftChild());
        if (n->HasRightChild())
            FoldPostOrder(f, par, acc, n->RightChild());
        f(n->dato, par, acc);
    }

    template<typename Data>
    void BinaryTree<Data>::MapInOrder(MapFunctor f, void *par, Node *n) // Accessory function executing from one node of the tree
    {
        if (n->HasLeftChild())
            MapInOrder(f, par, n->LeftChild());
        f(n->dato, par);
        if (n->HasRightChild())
            MapInOrder(f, par, n->RightChild());
    }

    template<typename Data>
    void BinaryTree<Data>::FoldInOrder(FoldFunctor f, const void *par, void *acc, Node *n) const // Accessory function executing from one node of the tree
    {
        if (n->HasLeftChild())
            FoldInOrder(f, par, acc, n->LeftChild());
        f(n->dato, par, acc);
        if (n->HasRightChild())
            FoldInOrder(f, par, acc, n->RightChild());
    }

    // Specific constructors
    template<typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(BinaryTree<Data> bt) // An iterator over a given binary tree
    {

    }

    /* ************************************************************************ */

    // Copy constructor
    template<typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator& poi)
    {

    }

    // Move constructor
    template<typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator&& poi) noexcept
    {

    }

    /* ************************************************************************ */

    // Destructor
    template<typename Data>
    BTPreOrderIterator<Data>::~BTPreOrderIterator()
    {

    }

    /* ************************************************************************ */

    // Copy assignment
    template<typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& poi)
    {

    }

    // Move assignment
    template<typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& poi) noexcept
    {

    }

    /* ************************************************************************ */

    // Comparison operators
    template<typename Data>
    bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator& poi) const noexcept
    {

    }

    template<typename Data>
    bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator& poi) const noexcept
    {

    }

    /* ************************************************************************ */

    // Specific member functions (inherited from Iterator)
    template<typename Data>
    Data& BTPreOrderIterator<Data>::operator*() const // (throw std::out_of_range when terminated)
    {

    }

    template<typename Data>
    bool BTPreOrderIterator<Data>::Terminated() const noexcept // (should not throw exceptions)
    {

    }

    /* ************************************************************************ */

    // Specific member functions (inherited from ForwardIterator)
    template<typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() // (throw std::out_of_range when terminated)
    {

    }

    /* ************************************************************************ */

    // Specific member functions (inherited from ResettableIterator)
    template<typename Data>
    void BTPreOrderIterator<Data>::Reset() noexcept  // (should not throw exceptions)
    {

    }
}
