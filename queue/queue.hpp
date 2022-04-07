
#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Queue : public Container{
              // Must extend Container

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~Queue() = default;

  /* ************************************************************************ */

  // Copy assignment
  virtual operator=(const Queue &q) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  virtual operator=(Queue &&q) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual operator==(const Queue &q) const noexcept = delete; // Comparison of abstract types might not be possible.
  virtual operator!=(const Queue &q) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  // type Head() specifiers; // (constant version; concrete function must throw std::length_error when empty)
  // type Head() specifiers; // (concrete function must throw std::length_error when empty)
  // type Dequeue() specifiers; // (concrete function must throw std::length_error when empty)
  // type HeadNDequeue() specifiers; // (concrete function must throw std::length_error when empty)
  void Enqueue(const Data &d) specifiers; // Copy of the value
  void Enqueue(Data &&d) specifiers; // Move of the value

};

/* ************************************************************************** */

}

#endif
