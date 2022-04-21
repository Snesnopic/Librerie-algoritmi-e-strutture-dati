namespace lasd
{

/* ************************************************************************** */

/* ************************************************************************ */

// Specific constructor
template <typename Data>
StackVec::StackVec(const LinearContainer<Data> &lc)
{
    size = lc.Size();
    array = new Data[size];
    for(unsigned long i = 0; i<size; i++)
        array[i] = lc[i];
    tail = size - 1;
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
StackVec::StackVec(const StackVec &sv)
{
    size = sv.size;
    tail = size - 1;
    array = new Data[sv.size];
    std::copy(sv.array,sv.array + size,array);
}
// Move constructor
template <typename Data>
StackVec::StackVec(StackVec &&sv) noexcept
{
    std::swap(array,sv.array);
    std::swap(size,sv.size);
    tail = size - 1;
}
/* ************************************************************************ */

// Destructor
template <typename Data>
StackVec::~StackVec()
{
    delete[] array;
}
/* ************************************************************************ */

// Copy assignment
template <typename Data>
StackVec& StackVec::operator=(const StackVec &sv)
{
    if(this != &sv)
    {
        Data *tmp = new Data[sv.size];
        std::copy(sv.array,sv.array + sv.size,tmp);
        delete []array;
        array = tmp;
        size = sv.size;
        tail = size - 1;
    }
    return *this;
}

// Move assignment
template <typename Data>
StackVec& StackVec::operator=(StackVec &&sv) noexcept
{
    if(this != &sv)
    {
        std::swap(array,sv.array);
        std::swap(size,sv.size);
        tail = size - 1;
    }
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool StackVec::operator==(const StackVec &sv) const noexcept
{
    if((tail  != sv.tail)
            return false;
            for(unsigned long i=0 ; i<=tail; i++)
    {
        if(array[i] != sv[i])
                return false;
        }
    return true;
}
template <typename Data>
bool StackVec::operator!=(const StackVec &sv) const noexcept
{
    return !(this == sv)
}

/* ************************************************************************ */

// Specific member functions (inherited from Stack)
template <typename Data>
const Data& StackVec::Top() const // Override Stack member (constant version; must throw std::length_error when empty)
{
    if(tail < 0)
        throw std::length_error("Length error!");
    return array[tail];
}
template <typename Data>
Data& StackVec::Top() // Override Stack member (must throw std::length_error when empty)
{
    if(tail < 0)
        throw std::length_error("Length error!");
    return array[tail];
}
template <typename Data>
void StackVec::Pop() // Override Stack member (must throw std::length_error when empty)
{
    if(tail < 0)
        throw std::length_error("Length error!");
    delete array[tail];
    tail--;
    if((tail + 1) == (size/4))
        Reduce();
}
template <typename Data>
Data& StackVec::TopNPop() // Override Stack member (must throw std::length_error when empty)
{
    if(tail < 0)
        throw std::length_error("Length error!");
    Data &ref = *(new Data(Top()));
    Pop();
    return ref;
}
template <typename Data>
void StackVec::Push(const Data& d) noexcept // Override Stack member (copy of the value)
{
    tail++;
    array[tail] = d;
}
template <typename Data>
void StackVec::Push(Data &&d) noexcept // Override Stack member (move of the value)
{
    tail++;
    if(tail == size)
        Expand();
    array[tail] = std::move(d);
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
bool StackVec::Empty() const noexcept // Override Container member
{
    return (tail < 0);
}
template <typename Data>
unsigned long StackVec::Size() const noexcept // Override Container member
{
    return (tail + 1);
}
template <typename Data>
void StackVec::Clear() // Override Container member
{
    delete []array;
    tail = -1;
    size = 0;
}
// Auxiliary member functions
template <typename Data>
void StackVec::Expand() noexcept
{
    Data* tmp = new Data[size * 2];
    for(unsigned long i = 0; i<size; i++)
    {
        std::swap(array[i],tmp[i]);
    }
    delete[] array;
    array = tmp;
    size = size * 2;
}
template <typename Data>
void StackVec::Reduce() noexcept
{
    Data* tmp = new Data[size / 2];
    for(unsigned long i = 0; i<=tail; i++)
    {
        std::swap(array[i],tmp[i]);
    }
    delete[] array;
    array = tmp;
    size = size / 2;
}
/* ************************************************************************** */

}
