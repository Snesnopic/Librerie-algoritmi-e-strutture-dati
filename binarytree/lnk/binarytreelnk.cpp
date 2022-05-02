namespace lasd
{

/* ************************************************************************** */
    template<typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(LinearContainer<Data>& lc) // A binary tree obtained from a LinearContainer
    {
        size = lc.Size();
    }

    /* ************************************************************************ */

    // Copy constructor
    template<typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk& btl)
    {
        size = btl.size;
        if (btl.root != nullptr)
        {
            root = new NodeLnk(btl.Root());
        }
    }

    // Move constructor
    template<typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk&& btl) noexcept
    {
        std::swap(root, btl.root);
        std::swap(size, btl.size);
    }

    /* ************************************************************************ */

    // Destructor
    template<typename Data>
    BinaryTreeLnk<Data>::~BinaryTreeLnk()
    {
        Clear();
    }

    /* ************************************************************************ */

    // Copy assignment
    template<typename Data>
    BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk& btl)
    {
        if (this != &btl)
        {
            size = btl.size;
            if (btl.root != nullptr)
            {
                root = new NodeLnk(btl.Root());
            }
        }
        return *this;
    }

    // Move assignment
    template<typename Data>
    BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk&& btl) noexcept
    {
        if (this != &btl)
        {
            std::swap(root, btl.root);
            std::swap(size, btl.size);
        }
        return *this;
    }

    template<typename Data>
    void BinaryTreeLnk<Data>::Clear()
    {
        if (root != nullptr)
            delete root;
        root = nullptr;
        size = 0;
    }
/* ************************************************************************** */

}
