
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>, virtual protected Vector<Data>{
                  // Must extend Stack<Data>,
                  //             Vector<Data>

private:

  // ...

protected:

    using Vector<Data>::array = nullptr;
    unsigned long head = 0;
    unsigned long tail = 0;
  // ...

public:

  // Default constructor
    StackVec() = default;

  /* ************************************************************************ */

  // Specific constructor
    StackVec(const LinearContainer<Data> &lc); // A stack obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
    StackVec(const StackVec &sv);

  // Move constructor
    StackVec(StackVec &&sv) noexcept;

  /* ************************************************************************ */

  // Destructor
    virtual ~StackVec();

  /* ************************************************************************ */

  // Copy assignment
    StackVec& operator=(const StackVec &sv);

  // Move assignment
    StackVec& operator=(StackVec &&sv) noexcept;

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const StackVec &sv) const noexcept;
    bool operator!=(const StackVec &sv) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

    const Data& Top() const override; // Override Stack member (constant version; must throw std::length_error when empty)
    Data& Top() override; // Override Stack member (must throw std::length_error when empty)
    void Pop() override; // Override Stack member (must throw std::length_error when empty)
    Data& TopNPop() override; // Override Stack member (must throw std::length_error when empty)
    void Push(const Data& d) noexcept override; // Override Stack member (copy of the value)
    void Push(Data &&d) noexcept override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

    bool Empty() const noexcept override; // Override Container member

    unsigned long Size() const noexcept override; // Override Container member

    void Clear() override; // Override Container member

protected:

  // Auxiliary member functions

    void Expand() noexcept;
    void Reduce() noexcept;

};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif