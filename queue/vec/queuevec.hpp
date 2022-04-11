
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : virtual public Queue<Data>,virtual protected Vector<Data>{
                  // Must extend Queue<Data>,
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
    QueueVec() = default;

  /* ************************************************************************ */

  // Specific constructor
    QueueVec(const LinearContainer<Data> &lc) specifiers; // A queue obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
    QueueVec(const QueueVec &qv);

  // Move constructor
    QueueVec(QueueVec &&qv) noexcept;

  /* ************************************************************************ */

  // Destructor
    virtual ~QueueVec();

  /* ************************************************************************ */

  // Copy assignment
    QueueVec& operator=(const QueueVec &qv);

  // Move assignment
    QueueVec& operator=(QueueVec &&qv) noexcept;

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const QueueVec &qv) const noexcept;
    bool operator!=(const QueueVec &qv) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

    const Data& Head() const override; // Override Queue member (constant version; must throw std::length_error when empty)
    Data& Head() override; // Override Queue member (must throw std::length_error when empty)
    void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
    Data& HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
    void Enqueue(const Data& d) noexcept override; // Override Queue member (copy of the value)
    void Enqueue(Data &&d) noexcept override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

    bool Empty() const noexcept override; // Override Container member

    unsigned int Size() const noexcept override; // Override Container member

    void Clear() noexcept override; // Override Container member

protected:

  // Auxiliary member functions

    void Expand() noexcept;
    void Reduce() noexcept;
    void SwapVectors(arguments) noexcept;

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif