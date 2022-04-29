#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

    template<typename Data>
    class QueueLst : virtual public Queue<Data>, virtual protected List<Data>
    {
        // Must extend Queue<Data>,
        //             List<Data>

    private:

        // ...

    protected:

        using List<Data>::head;
        using List<Data>::size;
        // ...

    public:

        // Default constructor
        QueueLst() = default;

        /* ************************************************************************ */

        // Specific constructor
        QueueLst(const LinearContainer<Data> &lc) : List<Data>(lc) {}; // A queue obtained from a LinearContainer

        /* ************************************************************************ */

        // Copy constructor
        QueueLst(const QueueLst &ql) : List<Data>(ql) {};

        // Move constructor
        QueueLst(QueueLst &&ql) noexcept: List<Data>(std::move(ql)) {};

        /* ************************************************************************ */

        // Destructor
        virtual ~QueueLst() = default;

        /* ************************************************************************ */

        // Copy assignment
        QueueLst &operator=(const QueueLst &ql);

        // Move assignment
        QueueLst &operator=(QueueLst &&ql) noexcept;

        /* ************************************************************************ */

        // Comparison operators
        bool operator==(const QueueLst &ql) const noexcept;

        bool operator!=(const QueueLst &ql) const noexcept;

        /* ************************************************************************ */

        // Specific member functions (inherited from Queue)

        const Data &Head() const override; // Override Queue member (constant version; must throw std::length_error when empty)
        Data &Head() override; // Override Queue member (must throw std::length_error when empty)
        void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
        Data &HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
        void Enqueue(const Data &d) noexcept override; // Override Queue member (copy of the value)
        void Enqueue(Data &&d) noexcept override; // Override Queue member (move of the value)

        /* ************************************************************************ */

        // Specific member functions (inherited from Container)

        void Clear() override; // Override Container member

    };

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
