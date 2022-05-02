namespace lasd
{

/* ************************************************************************** */

// Specific member functions (inherited from Container)
    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(LinearContainer<Data>& lc) // A binary tree obtained from a LinearContainer
    {
        size = lc.Size();
        array.Resize(size);
        for (unsigned long i = 0; i < array.Size(); i++)
        {
            NodeVec *n = new NodeVec(&array, i, lc[i]);
            array[i] = n;
        }
    }

    /* ************************************************************************ */

    // Copy constructor
    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec& btv)
    {
        size = btv.size;
        array.Resize(btv.array.Size());
        for (unsigned long i = 0; i < array.Size(); i++)
        {
            array[i] = new NodeVec(&array, i, btv.array[i]->dato);
        }
    }

    // Move constructor
    template<typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec&& btv) noexcept
    {
        std::swap(size, btv.size);
        std::swap(array, btv.array);
    }
    /* ************************************************************************ */

    // Destructor
    template<typename Data>
    BinaryTreeVec<Data>::~BinaryTreeVec()
    {
        Clear();
    }

    template<typename Data>
    void BinaryTreeVec<Data>::Clear() // Override Container member
    {
        for (unsigned long i = 0; i < array.Size(); i++)
        {
            if (array[i] != nullptr)
                delete array[i];
        }
        size = 0;
        array.Clear();
    }

    // Copy assignment
    template<typename Data>
    BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec& btv)
    {
        if (this != &btv)
        {
            array.Resize(btv.size);
            size = btv.size;
            for (unsigned long i = 0; i < size; i++)
            {
                array[i] = new NodeVec(&array, i, btv.array[i]->dato);
            }
        }
        return *this;
    }

    // Move assignment
    template<typename Data>
    BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec&& btv) noexcept
    {
        if (this != &btv)
        {
            std::swap(array, btv.array);
            std::swap(size, btv.size);
        }
        return *this;
    }

/* ************************************************************************** */

}
