
namespace lasd {

/* ************************************************************************** */

  /* ************************************************************************ */

  // Specific constructor
    using <typename Data>
    StackVec::StackVec(const LinearContainer<Data> &lc)
    {
        size = lc.Size();
        array = new Data[size];
        for(unsigned long i = 0; i<size; i++)
            array[i] = lc[i];
    }

  /* ************************************************************************ */

  // Copy constructor
    using <typename Data>
    StackVec::StackVec(const StackVec &sv)
    {
        size = sv.size;
        array = new Data[sv.size];
        std::copy(sv.array,sv.array + size,array);
    }
  // Move constructor
    using <typename Data>
    StackVec::StackVec(StackVec &&sv) noexcept
    {
        std::swap(array,sv.array);
        std::swap(size,sv.size);
    }
  /* ************************************************************************ */

  // Destructor
    virtual StackVec::~StackVec()
    {
        delete[] array;
    }
  /* ************************************************************************ */

  // Copy assignment
    StackVec& StackVec::operator=(const StackVec &sv)
    {
        if(this != &sv)
        {
            Data *tmp = new Data[sv.size];
            std::copy(sv.array,sv.array + sv.size,tmp);
            delete []array;
            array = tmp;
            size = sv.size;
        }
        return *this;
    }

  // Move assignment
    StackVec& StackVec::operator=(StackVec &&sv) noexcept
    {
        if(this != &sv)
        {
            std::swap(array,sv.array);
            std::swap(size,sv.size);
        }
        return *this;
    }

  /* ************************************************************************ */

  // Comparison operators
    bool StackVec::operator==(const StackVec &sv) const noexcept
    {
        if(size != sv.Size())
            return false;
        for(unsigned long i=0 ; i<size; i++)
        {
            if(array[i] != sv[i])
                return false;
        }
        return true;
    }
    bool StackVec::operator!=(const StackVec &sv) const noexcept
    {
        return !(this == sv)
    }

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

    const Data& StackVec::Top() const // Override Stack member (constant version; must throw std::length_error when empty)
    {
        if(size == 0)
            throw std::length_error("Length error!");
        return array[0];
    }
    Data& StackVec::Top() // Override Stack member (must throw std::length_error when empty)
    {
        if(size == 0)
            throw std::length_error("Length error!");
        return array[0];
    }
    void StackVec::Pop() // Override Stack member (must throw std::length_error when empty)
    {

    }
    Data& StackVec::TopNPop() // Override Stack member (must throw std::length_error when empty)
    {

    }
    void StackVec::Push(const Data& d) noexcept // Override Stack member (copy of the value)
    {

    }
    void StackVec::Push(Data &&d) noexcept // Override Stack member (move of the value)
    {

    }

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

    bool StackVec::Empty() const noexcept // Override Container member
    {

    }
    unsigned long StackVec::Size() const noexcept // Override Container member
    {

    }
    void StackVec::Clear() // Override Container member
    {

    }
  // Auxiliary member functions

    void StackVec::Expand() noexcept
    {

    }
    void StackVec::Reduce() noexcept
    {

    }
/* ************************************************************************** */

}
