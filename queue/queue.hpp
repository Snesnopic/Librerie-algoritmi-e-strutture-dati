#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

    template<typename Data>
    class Queue : virtual public Container
    {
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
        virtual Queue& operator=(const Queue& q) = delete; // Copy assignment of abstract types should not be possible.

        // Move assignment
        virtual Queue& operator=(Queue&& q) noexcept = delete; // Move assignment of abstract types should not be possible.

        /* ************************************************************************ */

        // Comparison operators
        virtual bool operator==(const Queue& q) const noexcept = delete; // Comparison of abstract types might not be possible.
        virtual bool operator!=(const Queue& q) const noexcept = delete; // Comparison of abstract types might not be possible.

        /* ************************************************************************ */

        // Specific member functions

        virtual const Data& Head() const = 0; // (constant version; concrete function must throw std::length_error when empty)
        virtual Data& Head() = 0; // (concrete function must throw std::length_error when empty)
        virtual void Dequeue() = 0; // (concrete function must throw std::length_error when empty)
        virtual Data& HeadNDequeue() = 0; // (concrete function must throw std::length_error when empty)
        virtual void Enqueue(const Data& d) noexcept = 0; // Copy of the value
        virtual void Enqueue(Data&& d) noexcept = 0; // Move of the value

    };

/* ************************************************************************** */

}

#endif
