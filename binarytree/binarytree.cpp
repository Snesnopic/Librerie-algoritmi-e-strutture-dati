namespace lasd
{

/* ************************************************************************** */
    template<typename Data>
    bool BinaryTree<Data>::Node::operator==(const Node& n) const noexcept
    {
        if (dato != n.dato)
            return false;
        if (HasLeftChild() && n.HasLeftChild())
        {
            if (LeftChild().operator!=(n.LeftChild()))
            {
                return false;
            }
        }
        if (HasRightChild() && n.HasRightChild())
        {
            if (RightChild().operator!=(n.RightChild()))
                return false;
        }
        return true;
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


/* ************************************************************************ */
    template<typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& bt) // An iterator over a given binary tree
    {
        curr = &bt.Root();
        treePtr = &bt;
    }

    template<typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++()  // (throw std::out_of_range when terminated)
    {
        if (Terminated())
            throw std::out_of_range("Out of range!");
        if (curr->HasRightChild())
            stack.Push(&curr->RightChild());
        if (curr->HasLeftChild())
            curr = &curr->LeftChild();
        else
        {
            if (!stack.Empty())
                curr = stack.TopNPop();
            else
                curr = nullptr;
        }
        return *this;
    }

/* ************************************************************************ */
    template<typename Data>
    struct BinaryTree<Data>::Node *BTPostOrderIterator<Data>::minLeaf(struct BinaryTree<Data>::Node *n)
    {
        struct BinaryTree<Data>::Node *tmp = n;
        stack.Push(tmp);
        if (tmp->HasRightChild())
            stack.Push(&tmp->RightChild());
        if (tmp->HasLeftChild())
        {
            return minLeaf(&tmp->LeftChild());
        }
        else
        {
            return stack.TopNPop();
        }
    }

    template<typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& bt) // An iterator over a given binary tree
    {
        treePtr = &bt;
        curr = minLeaf(&bt.Root());
    }

    template<typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() // (throw std::out_of_range when terminated)
    {
        if (Terminated())
            throw std::out_of_range("Out of range!");
        if (stack.Empty())
            curr = nullptr;
        else
        {
            if (stack.Top()->HasRightChild() && curr == &(stack.Top()->RightChild()))
                curr = stack.TopNPop();
            else
            {
                if (stack.Top()->HasRightChild())
                    curr = minLeaf(&(stack.TopNPop()->RightChild()));
                else
                    curr = stack.TopNPop();
            }
        }
        return *this;
    }

/* ************************************************************************ */
    template<typename Data>
    struct BinaryTree<Data>::Node *BTInOrderIterator<Data>::min(struct BinaryTree<Data>::Node *n)
    {
        struct BinaryTree<Data>::Node *tmp = n;
        if (tmp->HasRightChild())
            stack.Push(&tmp->RightChild());
        if (tmp->HasLeftChild())
        {
            stack.Push(tmp);
            tmp = min(&tmp->LeftChild());
        }
        return tmp;
    }

    template<typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& bt) // An iterator over a given binary tree
    {
        treePtr = &bt;
        curr = min(&bt.Root());
    }

    template<typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++()  // (throw std::out_of_range when terminated)
    {
        if (Terminated())
            throw std::out_of_range("Out of range!");
        if (curr->HasRightChild())
        {
            curr = min(&curr->RightChild());
            if (curr == stack.Top())
                stack.Pop();
        }
        else
        {
            if (stack.Empty())
                curr = nullptr;
            else
                curr = stack.TopNPop();
        }
        return *this;
    }

/* ************************************************************************ */
    template<typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& bt) // An iterator over a given binary tree
    {
        curr = &bt.Root();
        treePtr = &bt;
    }

    template<typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++()  // (throw std::out_of_range when terminated)
    {
        if (Terminated())
            throw std::out_of_range("Out of range!");
        if (curr->HasLeftChild())
            que.Enqueue(&curr->LeftChild());
        if (curr->HasRightChild())
            que.Enqueue(&curr->RightChild());
        if (!que.Empty())
            curr = que.HeadNDequeue();
        else
            curr = nullptr;
        return *this;
    }
}
