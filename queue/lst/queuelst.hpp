
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst : virtual public Queue<Data>,virtual protected List<Data>{
                  // Must extend Queue<Data>,
                  //             List<Data>

private:

  // ...

protected:

  using List<Data>::Node;

  // ...

public:

  // Default constructor
    QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructor
    QueueLst(const LinearContainer<Data> &lc) specifiers; // A queue obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
    QueueLst(const Queue &q);

  // Move constructor
    QueueLst(Queue &&q) noexcept;

  /* ************************************************************************ */

  // Destructor
    ~QueueLst();

  /* ************************************************************************ */

  // Copy assignment
    Queue& operator=(const Queue& q);

  // Move assignment
    Queue& operator=(Queue&& q) noexcept;

  /* ************************************************************************ */

  // Comparison operators
    bool operator==(const Queue& q) const noexcept;
    bool operator!=(const Queue& q) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

    void Head(); // Override Queue member (constant version; must throw std::length_error when empty)
    Data& Head(); // Override Queue member (must throw std::length_error when empty)
    void Dequeue(); // Override Queue member (must throw std::length_error when empty)
    Data& HeadNDequeue(); // Override Queue member (must throw std::length_error when empty)
    void Enqueue(const Data& d) noexcept; // Override Queue member (copy of the value)
    void Enqueue(Data&& d) noexcept; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

    void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
