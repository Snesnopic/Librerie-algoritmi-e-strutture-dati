// #include "..."

namespace lasd
{

/* ************************************************************************** */
    template<typename Data>
    bool BinaryTree<Data>::Node::operator==(const Node& n) const noexcept
    {
        if(dato != n.dato)
            return false;
        if(HasRightChild() && n.HasRightChild())
        {
            if(RightChild() == n.RightChild())
            {
                if(HasLeftChild() & n.HasLeftChild())
                {
                    if(LeftChild() == n.LeftChild())
                        return true;
                }
            }
        }
        return false;
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
        MapPreOrder(f, par, &Root());
    }

    template<typename Data>
    void BinaryTree<Data>::Fold(FoldFunctor f, const void *par, void *acc) const  // Override FoldableContainer member
    {
        FoldPreOrder(f, par, acc, &Root());
    }

    template<typename Data>
    void BinaryTree<Data>::MapPreOrder(MapFunctor f, void *par)  // Override PreOrderMappableContainer member
    {
        MapPreOrder(f, par, &Root());
    }

    template<typename Data>
    void BinaryTree<Data>::FoldPreOrder(FoldFunctor f, const void *par, void *acc) const  // Override PreOrderFoldableContainer member
    {
        FoldPreOrder(f, par, acc, &Root());
    }

    template<typename Data>
    void BinaryTree<Data>::MapPostOrder(MapFunctor f, void *par) // Override PostOrderMappableContainer member
    {
        MapPostOrder(f, par, &Root());
    }

    template<typename Data>
    void BinaryTree<Data>::FoldPostOrder(FoldFunctor f, const void *par, void *acc) const // Override PostOrderFoldableContainer member
    {
        FoldPostOrder(f, par, acc, &Root());
    }

    template<typename Data>
    void BinaryTree<Data>::MapInOrder(MapFunctor f, void *par) // Override InOrderMappableContainer member
    {
        MapInOrder(f, par, &Root());
    }

    template<typename Data>
    void BinaryTree<Data>::FoldInOrder(FoldFunctor f, const void *par, void *acc) const // Override InOrderFoldableContainer member
    {
        FoldInOrder(f, par, acc, &Root());
    }

    template<typename Data>
    void BinaryTree<Data>::MapBreadth(MapFunctor f, void *par) // Override BreadthMappableContainer member
    {
            QueueLst<Node *> queue{};
            queue.Enqueue(&Root());
            Node *n = nullptr;
            while (!queue.Empty())
            {
                n = queue.Head();
                f(n->dato, par);
                queue.Dequeue();
                if (n->HasLeftChild())
                    queue.Enqueue(&n->LeftChild());
                if (n->HasRightChild())
                    queue.Enqueue(&n->RightChild());
            }
    }

    template<typename Data>
    void BinaryTree<Data>::FoldBreadth(FoldFunctor f, const void *par, void *acc) const  // Override BreadthFoldableContainer member
    {

            QueueLst<Node *> queue{};
            queue.Enqueue(&Root());
            Node *n = nullptr;
            while (!queue.Empty())
            {
                n = queue.Head();
                f(n->dato, par, acc);
                queue.Dequeue();
                if (n->HasLeftChild())
                    queue.Enqueue(&n->LeftChild());
                if (n->HasRightChild())
                    queue.Enqueue(&n->RightChild());
            }

    }


    template<typename Data>
    void BinaryTree<Data>::MapPreOrder(MapFunctor f, void *par, Node *n) // Accessory function executing from one node of the tree
    {
        f(n->dato, par);
        if (n->HasLeftChild())
            MapPreOrder(f, par, &n->LeftChild());
        if (n->HasRightChild())
            MapPreOrder(f, par, &n->RightChild());
    }

    template<typename Data>
    void BinaryTree<Data>::FoldPreOrder(FoldFunctor f, const void *par, void *acc, Node *n) const // Accessory function executing from one node of the tree
    {
        f(n->dato, par, acc);
        if (n->HasLeftChild())
            FoldPreOrder(f, par, acc, &n->LeftChild());
        if (n->HasRightChild())
            FoldPreOrder(f, par, acc, &n->RightChild());
    }

    template<typename Data>
    void BinaryTree<Data>::MapPostOrder(MapFunctor f, void *par, Node *n) // Accessory function executing from one node of the tree
    {
        if (n->HasLeftChild())
            MapPostOrder(f, par, &n->LeftChild());
        if (n->HasRightChild())
            MapPostOrder(f, par, &n->RightChild());
        f(n->dato, par);
    }

    template<typename Data>
    void BinaryTree<Data>::FoldPostOrder(FoldFunctor f, const void *par, void *acc, Node *n) const // Accessory function executing from one node of the tree
    {
        if (n->HasLeftChild())
            FoldPostOrder(f, par, acc, &n->LeftChild());
        if (n->HasRightChild())
            FoldPostOrder(f, par, acc, &n->RightChild());
        f(n->dato, par, acc);
    }

    template<typename Data>
    void BinaryTree<Data>::MapInOrder(MapFunctor f, void *par, Node *n) // Accessory function executing from one node of the tree
    {
        if (n->HasLeftChild())
            MapInOrder(f, par, &n->LeftChild());
        f(n->dato, par);
        if (n->HasRightChild())
            MapInOrder(f, par, &n->RightChild());
    }

    template<typename Data>
    void BinaryTree<Data>::FoldInOrder(FoldFunctor f, const void *par, void *acc, Node *n) const // Accessory function executing from one node of the tree
    {
        if (n->HasLeftChild())
            FoldInOrder(f, par, acc, &n->LeftChild());
        f(n->dato, par, acc);
        if (n->HasRightChild())
            FoldInOrder(f, par, acc, &n->RightChild());
    }

}
