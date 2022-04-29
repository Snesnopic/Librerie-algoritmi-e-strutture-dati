namespace lasd
{

/* ************************************************************************** */

// Copy assignment
    template<typename Data>
    StackLst<Data> &StackLst<Data>::operator=(const StackLst &sl)
    {
        List<Data>::operator=(sl);
        return *this;
    }

// Move assignment
    template<typename Data>
    StackLst<Data> &StackLst<Data>::operator=(StackLst &&sl) noexcept
    {
        List<Data>::operator=(std::move(sl));
        return *this;
    }

/* ************************************************************************ */

// Comparison operators
    template<typename Data>
    bool StackLst<Data>::operator==(const StackLst &sl) const noexcept
    {
        return List<Data>::operator==(sl);
    }

    template<typename Data>
    bool StackLst<Data>::operator!=(const StackLst &sl) const noexcept
    {
        return List<Data>::operator!=(sl);
    }

/* ************************************************************************ */

// Specific member functions (inherited from Stack)
    template<typename Data>
    const Data &StackLst<Data>::Top() const // Override Stack member (constant version; must throw std::length_error when empty)
    {
        return List<Data>::Front();
    }

    template<typename Data>
    Data &StackLst<Data>::Top() // Override Stack member (must throw std::length_error when empty)
    {
        return List<Data>::Front();
    }

    template<typename Data>
    void StackLst<Data>::Pop() // Override Stack member (must throw std::length_error when empty)
    {
        List<Data>::RemoveFromFront();
    }

    template<typename Data>
    Data &StackLst<Data>::TopNPop() // Override Stack member (must throw std::length_error when empty)
    {
        return List<Data>::FrontNRemove();
    }

    template<typename Data>
    void StackLst<Data>::Push(const Data &d) // Override Stack member (copy of the value)
    {
        List<Data>::InsertAtFront(d);
    }

    template<typename Data>
    void StackLst<Data>::Push(Data &&d) noexcept// Override Stack member (move of the value)
    {
        List<Data>::InsertAtFront(std::move(d));
    }

/* ************************************************************************ */

// Specific member functions (inherited from Container)
    template<typename Data>
    void StackLst<Data>::Clear() // Override Container member
    {
        List<Data>::Clear();
    }

/* ************************************************************************** */

}
