#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>, virtual protected List<Data>
{
    // Must extend Stack<Data>,
    //             List<Data>

private:

    // ...

protected:
    using List<Data>::head;
    using List<Data>::size;
    // ...

public:

    // Default constructor
    StackLst() = default;

    /* ************************************************************************ */

    // Specific constructor
    StackLst(const LinearContainer<Data> &lc) : List<Data>(lc){}; // A stack obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    StackLst(const StackLst &sl) : List<Data>(sl){};

    // Move constructor
    StackLst(StackLst &&sl) noexcept : List<Data>(std::move(sl)){};

    /* ************************************************************************ */

    // Destructor
    virtual ~StackLst() = default;

    /* ************************************************************************ */

    // Copy assignment
    StackLst& operator=(const StackLst &sl);

    // Move assignment
    StackLst& operator=(StackLst &&sl) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const StackLst &sl) const noexcept;
    bool operator!=(const StackLst &sl) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from Stack)

    const Data& Top() const override; // Override Stack member (constant version; must throw std::length_error when empty)
    Data& Top() override; // Override Stack member (must throw std::length_error when empty)
    void Pop() override; // Override Stack member (must throw std::length_error when empty)
    Data& TopNPop() override; // Override Stack member (must throw std::length_error when empty)
    void Push(const Data& d) override; // Override Stack member (copy of the value)
    void Push(Data &&d) noexcept override; // Override Stack member (move of the value)

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
