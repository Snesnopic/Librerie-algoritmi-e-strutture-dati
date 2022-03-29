#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

#include <stdexcept>
#include <functional>

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

class Container
{

private:

    // ...

protected:

    unsigned long size = 0;

public:

    // Destructor
    virtual ~Container();

    /* ************************************************************************ */

    // Copy assignment
    virtual Container& operator=(Container c) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual Container& operator=(Container &&c) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(Container &c1) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(Container &c1) const = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    bool Empty() const noexcept; // (concrete function should not throw exceptions)

    unsigned long Size() const noexcept; // (concrete function should not throw exceptions)

    virtual void Clear();

};

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public Container  // Must extend Container
{

private:

    // ...

protected:

    // ...

public:

    // Destructor
    virtual ~LinearContainer();

    /* ************************************************************************ */

    // Copy assignment
    virtual LinearContainer& operator=(LinearContainer lc) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual LinearContainer& operator=(LinearContainer &&lc) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(LinearContainer &c) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(LinearContainer &c) const = delete; // Comparison of abstract types is possible.

    /* ************************************************************************ */

    // Specific member functions

    Data Front() const; // (concrete function must throw std::length_error when empty)
    Data Back() const; // (concrete function must throw std::length_error when empty)

    virtual Data& operator[](const unsigned long index); // (concrete function must throw std::out_of_range when out of range)

};

/* ************************************************************************** */

template <typename Data>
class TestableContainer : virtual public Container  // Must extend Container
{

private:

    // ...

protected:

    // ...

public:

    // Destructor
    virtual ~TestableContainer();

    /* ************************************************************************ */

    // Copy assignment
    virtual TestableContainer& operator=(TestableContainer tc) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual TestableContainer& operator=(TestableContainer &&tc) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(TestableContainer &tc) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(TestableContainer &tc) const = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    virtual bool Exists(const Data &d) const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class MappableContainer : virtual public Container  // Must extend Container
{

private:

    // ...

protected:

    // ...

public:

    // Destructor
    virtual ~MappableContainer();

    /* ************************************************************************ */

    // Copy assignment
    virtual MappableContainer& operator=(MappableContainer mc) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual MappableContainer& operator=(MappableContainer &&mc) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(MappableContainer &mc) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(MappableContainer &mc) const = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    typedef std::function<void(Data&, void*)> MapFunctor;
    virtual void Map(MapFunctor,void*) = 0;

};

/* ************************************************************************** */

template <typename Data>
class FoldableContainer : virtual public TestableContainer<Data>  // Must extend TestableContainer<Data>
{

private:

    // ...

protected:

    // ...

public:

    // Destructor
    virtual ~FoldableContainer();

    /* ************************************************************************ */

    // Copy assignment
    virtual FoldableContainer& operator=(FoldableContainer fc) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual FoldableContainer& operator=(FoldableContainer &&fc) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(FoldableContainer &fc) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(FoldableContainer &fc) const = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    typedef std::function<void(const Data&, const void*, void*)> FoldFunctor;

    virtual void Fold(FoldFunctor, const void*,void*)const = delete;

    /* ************************************************************************ */

    // Specific member functions (inherited from TestableContainer)

   inline virtual bool Exists(const Data &d)const noexcept override; // Override TestableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer : virtual public MappableContainer<Data>  // Must extend MappableContainer<Data>
{

private:

    // ...

protected:

    // ...

public:

    // Destructor
    virtual ~PreOrderMappableContainer();

    /* ************************************************************************ */

    // Copy assignment
    virtual PreOrderMappableContainer& operator=(PreOrderMappableContainer pomc) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual PreOrderMappableContainer& operator=(PreOrderMappableContainer &&pomc) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(PreOrderMappableContainer &pomc) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(PreOrderMappableContainer &pomc) const = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type MapInOrder(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    // type Map(argument) override specifiers; // Override MappableContainer member
    //Map farà stab a MapInOrder
};

/* ************************************************************************** */

template <typename Data>
class PreOrderFoldableContainer : virtual public FoldableContainer<Data>  // Must extend FoldableContainer<Data>
{

private:

    // ...

protected:

    // ...

public:

    // Destructor
    virtual ~PreOrderFoldableContainer();

    /* ************************************************************************ */

    // Copy assignment
    virtual PreOrderFoldableContainer& operator=(PreOrderFoldableContainer pofc) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual PreOrderFoldableContainer& operator=(PreOrderFoldableContainer &&pofc) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(PreOrderFoldableContainer &pofc) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(PreOrderFoldableContainer &pofc) const = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type FoldInOrder(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    // type Fold(argument) specifiers; // Override FoldableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer :virtual public MappableContainer<Data>  // Must extend MappableContainer<Data>
{

private:

    // ...

protected:

    // ...

public:

    // Destructor
    virtual ~PostOrderMappableContainer();

    /* ************************************************************************ */

    // Copy assignment
    virtual PostOrderMappableContainer operator=(PostOrderMappableContainer pomc) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual PostOrderMappableContainer operator=(PostOrderMappableContainer &&pomc) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(PostOrderMappableContainer &pomc) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(PostOrderMappableContainer &pomc) const = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type MapInOrder(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    // type Map(argument) specifiers; // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderFoldableContainer : virtual public FoldableContainer<Data>  // Must extend FoldableContainer<Data>
{

private:

    // ...

protected:

    // ...

public:

    // Destructor
    virtual ~PostOrderFoldableContainer();

    /* ************************************************************************ */

    // Copy assignment
    virtual PostOrderFoldableContainer operator=(PostOrderFoldableContainer pofc) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual PostOrderFoldableContainer operator=(PostOrderFoldableContainer &&pofc) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(PostOrderFoldableContainer &pofc) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(PostOrderFoldableContainer &pofc) const = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type FoldInOrder(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    // type Fold(argument) specifiers; // Override FoldableContainer member

};

/* ************************************************************************** */

template <typename Data>
class InOrderMappableContainer : virtual public MappableContainer<Data>  // Must extend MappableContainer<Data>
{

private:

    // ...

protected:

    // ...

public:

    // Destructor
    virtual ~InOrderMappableContainer();

    /* ************************************************************************ */

    // Copy assignment
    virtual InOrderMappableContainer operator=(InOrderMappableContainer iomc) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual InOrderMappableContainer operator=(InOrderMappableContainer &&iomc) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(InOrderMappableContainer &iomc) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(InOrderMappableContainer &iomc) const = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type MapInOrder(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    // type Map(argument) specifiers; // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class InOrderFoldableContainer : virtual public FoldableContainer<Data>  // Must extend FoldableContainer<Data>
{

private:

    // ...

protected:

    // ...

public:

    // Destructor
    virtual ~InOrderFoldableContainer();

    /* ************************************************************************ */

    // Copy assignment
    virtual InOrderFoldableContainer operator=(InOrderFoldableContainer iofc) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual InOrderFoldableContainer operator=(InOrderFoldableContainer &&iofc) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(InOrderFoldableContainer &iofc) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(InOrderFoldableContainer &iofc) const = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type FoldInOrder(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    // type Fold(argument) specifiers; // Override FoldableContainer member

};

/* ************************************************************************** */

template <typename Data>
class BreadthMappableContainer : virtual public MappableContainer<Data>   // Must extend MappableContainer<Data>
{

private:

    // ...

protected:

    // ...

public:

    // Destructor
    virtual ~BreadthMappableContainer();

    /* ************************************************************************ */

    // Copy assignment
    virtual BreadthMappableContainer operator=(BreadthMappableContainer bmc) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual BreadthMappableContainer operator=(BreadthMappableContainer &&bmc) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(BreadthMappableContainer &bmc) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(BreadthMappableContainer &bmc) const = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type MapBreadth(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    // type Map(argument) specifiers; // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class BreadthFoldableContainer : virtual public FoldableContainer<Data>  // Must extend FoldableContainer<Data>
{

private:

    // ...

protected:

    // ...

public:

    // Destructor
    virtual ~BreadthFoldableContainer();

    /* ************************************************************************ */

    // Copy assignment
    virtual BreadthFoldableContainer operator=(BreadthFoldableContainer bfc) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    virtual BreadthFoldableContainer operator=(BreadthFoldableContainer &&bfc) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    virtual bool operator==(BreadthFoldableContainer &bfc) const = delete; // Comparison of abstract types might not be possible.
    virtual bool operator!=(BreadthFoldableContainer &bfc) const = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename FoldableContainer<Data>::FoldFunctor;

    // type FoldBreadth(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    // type Fold(argument) specifiers; // Override FoldableContainer member

};

/* ************************************************************************** */

}

#include "container.cpp"

#endif
