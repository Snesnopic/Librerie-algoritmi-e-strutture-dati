namespace lasd
{

/* ************************************************************************** */
// Move constructor
    template<typename Data>
    StackVec<Data>::StackVec(StackVec &&sv) noexcept
    {
        std::swap(array, sv.array);
        std::swap(size, sv.size);
        std::swap(tail, sv.tail);
    }
/* ************************************************************************ */

// Copy assignment
    template<typename Data>
    StackVec<Data> &StackVec<Data>::operator=(const StackVec &sv)
    {
        Vector<Data>::operator=(sv);
        tail = sv.tail;
        return *this;
    }

// Move assignment
    template<typename Data>
    StackVec<Data> &StackVec<Data>::operator=(StackVec &&sv) noexcept
    {
        Vector<Data>::operator=(std::move(sv));
        tail = std::move(sv.tail);
        return *this;
    }

/* ************************************************************************ */

// Comparison operators
    template<typename Data>
    bool StackVec<Data>::operator==(const StackVec &sv) const noexcept
    {
        if (tail != sv.tail)
            return false;
        for (unsigned long i = 0; i <= tail; i++)
        {
            if (array[i] != sv[i])
                return false;
        }
        return true;
    }

    template<typename Data>
    bool StackVec<Data>::operator!=(const StackVec &sv) const noexcept
    {
        return !(*this == sv);
    }

/* ************************************************************************ */

// Specific member functions (inherited from Stack)
    template<typename Data>
    const Data &StackVec<Data>::Top() const // Override Stack member (constant version; must throw std::length_error when empty)
    {
        if (tail < 0)
            throw std::length_error("Length error!");
        return array[tail];
    }

    template<typename Data>
    Data &StackVec<Data>::Top() // Override Stack member (must throw std::length_error when empty)
    {
        if (tail < 0)
            throw std::length_error("Length error!");
        return array[tail];
    }

    template<typename Data>
    void StackVec<Data>::Pop() // Override Stack member (must throw std::length_error when empty)
    {
        if (tail < 0)
            throw std::length_error("Length error!");
        tail--;
        if ((tail + 1) <= (size / 4))
            Reduce();
    }

    template<typename Data>
    Data &StackVec<Data>::TopNPop() // Override Stack member (must throw std::length_error when empty)
    {
        if (tail < 0)
            throw std::length_error("Length error!");
        Data &ref = *(new Data(Top()));
        Pop();
        return ref;
    }

    template<typename Data>
    void StackVec<Data>::Push(const Data &d) // Override Stack member (copy of the value)
    {
        tail++;
        if (tail == size)
            Expand();
        array[tail] = d;
    }

    template<typename Data>
    void StackVec<Data>::Push(Data &&d) noexcept // Override Stack member (move of the value)
    {
        tail++;
        if (tail == size)
            Expand();
        array[tail] = std::move(d);
    }

/* ************************************************************************ */

// Specific member functions (inherited from Container)
    template<typename Data>
    bool StackVec<Data>::Empty() const noexcept // Override Container member
    {
        return (tail < 0);
    }

    template<typename Data>
    unsigned long StackVec<Data>::Size() const noexcept // Override Container member
    {
        return (tail + 1);
    }

    template<typename Data>
    void StackVec<Data>::Clear() // Override Container member
    {
        Vector<Data>::Clear();
        tail = -1;
    }

// Auxiliary member functions
    template<typename Data>
    void StackVec<Data>::Expand() noexcept
    {
        Data *tmp = new Data[size * 2];
        for (unsigned long i = 0; i < size; i++)
        {
            std::swap(array[i], tmp[i]);
        }
        delete[] array;
        array = tmp;
        size = size * 2;
    }

    template<typename Data>
    void StackVec<Data>::Reduce() noexcept
    {
        Data *tmp = new Data[size / 2];
        for (unsigned long i = 0; i < tail + 1; i++)
        {
            std::swap(array[i], tmp[i]);
        }
        delete[] array;
        array = tmp;
        size = size / 2;
    }
/* ************************************************************************** */

}
