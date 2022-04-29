// #include "..."

namespace lasd
{

/* ************************************************************************** */
    template<typename Data>
    bool BinaryTree<Data>::Node::operator==(const Node &n) const noexcept
    {
        if (this == nullptr && n == nullptr)
            return true;
        return ((dato == n.dato) && (RightChild() == n.rightChild()) && (LeftChild() == n.LeftChild()));
    }

    template<typename Data>
    bool BinaryTree<Data>::Node::operator!=(const Node &n) const noexcept
    {
        return !(*this == n);
    }

    template<typename Data>
    bool BinaryTree<Data>::operator==(const BinaryTree &bt) const noexcept
    {
        if (size == bt.size)
            return Root() == bt.Root();
        return false;
    }

    template<typename Data>
    bool BinaryTree<Data>::operator!=(const BinaryTree &bt) const noexcept
    {
        return !(*this == bt);
    }
/* ************************************************************************** */

}
