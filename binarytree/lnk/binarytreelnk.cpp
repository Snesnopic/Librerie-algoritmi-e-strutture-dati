namespace lasd
{

/* ************************************************************************** */
    template<typename Data>
    BinaryTree<Data>::NodeLnk(const Data& d)
    {

    }
    template<typename Data>
    BinaryTree<Data>::NodeLnk::NodeLnk(Data& d)
    {

    }
    template<typename Data>
    Data& BinaryTree<Data>::NodeLnk::Element() noexcept // Mutable access to the element (concrete function should not throw exceptions)
    {

    }
    template<typename Data>
    const Data& BinaryTree<Data>::NodeLnk::Element() const noexcept // Immutable access to the element (concrete function should not throw exceptions)
    {

    }
    template<typename Data>
    bool BinaryTree<Data>::Node::HasLeftChild() const noexcept // (concrete function should not throw exceptions)
    {

    }
    template<typename Data>
    bool BinaryTree<Data>::Node::HasRightChild() const noexcept // (concrete function should not throw exceptions)
    {

    }
    template<typename Data>
    NodeLnk& BinaryTree<Data>::Node::LeftChild() const // (concrete function must throw std::out_of_range when not existent)
    {

    }
    template<typename Data>
    NodeLnk& BinaryTree<Data>::Node::RightChild() const // (concrete function must throw std::out_of_range when not existent)
    {

    }

/* ************************************************************************** */

}
