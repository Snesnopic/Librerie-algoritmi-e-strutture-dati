namespace lasd
{

    /* ************************************************************************** */

    // Specific constructor
    template <typename Data>
    QueueVec<Data>::QueueVec(const LinearContainer<Data> &lc) // A queue obtained from a LinearContainer
    {
        size = lc.Size();
        capacity = size;
        array = new Data[capacity];
        for(unsigned long i = 0; i < size ; i++)
            array[i] = lc[i];
        tail = size - 1;
    }

    /* ************************************************************************ */

    // Copy constructor
    template <typename Data>
    QueueVec<Data>::QueueVec(const QueueVec &qv)
    {
        size = qv.size;
        tail = size - 1;
        array = new Data[size];
        for(unsigned long i = 0; i < size ; i++)
            array[i] = qv.array[(i + qv.head) & qv.capacity];
    }

    // Move constructor
    template <typename Data>
    QueueVec<Data>::QueueVec(QueueVec &&qv) noexcept
    {

    }

    /* ************************************************************************ */

    // Destructor
    template <typename Data>
    QueueVec<Data>::~QueueVec()
    {
        delete []array;
    }

    /* ************************************************************************ */

    // Copy assignment
    template <typename Data>
    QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec &qv)
    {
        if(this != &qv)
        {
            size = qv.size;
            tail = size - 1;
            array = new Data[size];
            for(unsigned long i = 0; i < size ; i++)
                array[i] = qv.array[(i + qv.head) & qv.capacity];
        }
        return *this;
    }

    // Move assignment
    template <typename Data>
    QueueVec<Data>& QueueVec<Data>::operator=(QueueVec &&qv) noexcept
    {
        if(this != &qv)
        {

        }
        return *this;
    }

    /* ************************************************************************ */

    // Comparison operators
    template <typename Data>
    bool QueueVec<Data>::operator==(const QueueVec &qv) const noexcept
    {
        if(size == qv.size)
        {
            for(unsigned long i = 0; i < size; i++)
            {
                if(array[(head + i) % capacity] != qv.array[(qv.head + i) & qv.capacity])
                    return false;
            }
            return true;
        }
        return false;
    }
    template <typename Data>
    bool QueueVec<Data>::operator!=(const QueueVec &qv) const noexcept
    {
        return !(*this == qv);
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from Queue)
    template <typename Data>
    const Data& QueueVec<Data>::Head() const // Override Queue member (constant version; must throw std::length_error when empty)
    {
        if(capacity == 0)
            throw std::length_error("Length error!");
        return array[head];
    }
    template <typename Data>
    Data& QueueVec<Data>::Head() // Override Queue member (must throw std::length_error when empty)
    {
        if(capacity == 0)
            throw std::length_error("Length error!");
        return array[head];
    }
    template <typename Data>
    void QueueVec<Data>::Dequeue() // Override Queue member (must throw std::length_error when empty)
    {
        if(size == 0)
            throw std::length_error("Length error!");
        head = (head + 1) % capacity;
        size--;
    }
    template <typename Data>
    Data& QueueVec<Data>::HeadNDequeue() // Override Queue member (must throw std::length_error when empty)
    {
        if(size == 0)
            throw std::length_error("Length error!");
        Data &ref = *(new Data(Head()));
        Dequeue();
        return ref;
    }
    template <typename Data>
    void QueueVec<Data>::Enqueue(const Data& d) noexcept // Override Queue member (copy of the value)
    {
        size++;
        if(size > capacity)
            Expand();
        tail = (tail + 1) % capacity;
        array[tail] = d;

    }
    template <typename Data>
    void QueueVec<Data>::Enqueue(Data &&d) noexcept // Override Queue member (move of the value)
    {
        size++;
        if(size > capacity)
            Expand();
        tail = (tail + 1) % capacity;
        array[tail] = std::move(d);
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)
    template <typename Data>
    bool QueueVec<Data>::Empty() const noexcept // Override Container member
    {
        return (size == 0);
    }
    template <typename Data>
    unsigned long QueueVec<Data>::Size() const noexcept // Override Container member
    {
        return size;
    }
    template <typename Data>
    void QueueVec<Data>::Clear() noexcept // Override Container member
    {
        delete []array;
        size = 0;
        head = 0;
        capacity = 0;
        tail = -1;
    }


    // Auxiliary member functions
    template <typename Data>
    void QueueVec<Data>::Expand() noexcept
    {
        Data* tmp = new Data[capacity * 2];
        SwapVectors(tmp);
        capacity = capacity * 2;
    }
    template <typename Data>
    void QueueVec<Data>::Reduce() noexcept
    {
        Data* tmp = new Data[capacity / 2];
        SwapVectors(tmp);
        capacity = capacity / 2;
    }
    template <typename Data>
    void QueueVec<Data>::SwapVectors(Data *tmp) noexcept
    {
        for(unsigned long i = 0; i < capacity; i++)
        {
            std::swap(array[(i + head) % capacity],tmp[i]);
        }
        delete[] array;
        array = tmp;
    }

/* ************************************************************************** */

}
