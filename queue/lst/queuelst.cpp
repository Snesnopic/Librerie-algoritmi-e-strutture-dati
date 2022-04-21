namespace lasd
{

/* ************************************************************************** */

    // Copy assignment
    template <typename Data>
    QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst& ql)
    {
        List<Data>::operator=(ql);
        return *this;
    }

    // Move assignment
    template <typename Data>
    QueueLst<Data>& QueueLst<Data>::operator=(QueueLst&& ql) noexcept
    {
        List<Data>::operator=(std::move(ql));
        return *this;
    }

    /* ************************************************************************ */

    // Comparison operators
    template <typename Data>
    bool QueueLst<Data>::operator==(const QueueLst& ql) const noexcept
    {
        return List<Data>::operator==(ql);
    }
    template <typename Data>
    bool QueueLst<Data>::operator!=(const QueueLst& ql) const noexcept
    {
        return !(*this == ql);
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from Queue)
    template <typename Data>
    const Data& QueueLst<Data>::Head() const // Override Queue member (constant version; must throw std::length_error when empty)
    {
        return List<Data>::Front();
    }
    template <typename Data>
    Data& QueueLst<Data>::Head() // Override Queue member (must throw std::length_error when empty)
    {
        return List<Data>::Front();
    }
    template <typename Data>
    void QueueLst<Data>::Dequeue() // Override Queue member (must throw std::length_error when empty)
    {
        List<Data>::RemoveFromFront();
    }
    template <typename Data>
    Data& QueueLst<Data>::HeadNDequeue() // Override Queue member (must throw std::length_error when empty)
    {
        return List<Data>::FrontNRemove();
    }
    template <typename Data>
    void QueueLst<Data>::Enqueue(const Data& d) noexcept // Override Queue member (copy of the value)
    {
        List<Data>::InsertAtBack(d);
    }
    template <typename Data>
    void QueueLst<Data>::Enqueue(Data &&d) noexcept // Override Queue member (move of the value)
    {
        List<Data>::InsertAtBack(std::move(d));
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)
    template <typename Data>
    void QueueLst<Data>::Clear() // Override Container member
    {
        List<Data>::Clear();

    }

/* ************************************************************************** */

}
