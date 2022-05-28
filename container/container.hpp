#pragma once
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
		virtual ~Container() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual Container& operator=(const Container& c) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual Container& operator=(Container&& c) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const Container& c1) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const Container& c1) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		virtual bool Empty() const noexcept; // (concrete function should not throw exceptions)

		virtual unsigned long Size() const noexcept; // (concrete function should not throw exceptions)

		virtual void Clear() = 0;

	};

/* ************************************************************************** */

	template<typename Data>
	class LinearContainer : virtual public Container  // Must extend Container
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~LinearContainer() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual LinearContainer& operator=(const LinearContainer& lc) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual LinearContainer& operator=(LinearContainer&& lc) noexcept = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const LinearContainer& c) const noexcept; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const LinearContainer& c) const noexcept; // Comparison of abstract types is possible.

		/* ************************************************************************ */

		// Specific member functions

		virtual Data& Front() const; // (concrete function must throw std::length_error when empty)
		virtual Data& Back() const; // (concrete function must throw std::length_error when empty)

		virtual Data& operator[](const unsigned long index) const = 0; // (concrete function must throw std::out_of_range when out of range)

	};

/* ************************************************************************** */

	template<typename Data>
	class TestableContainer : virtual public Container  // Must extend Container
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~TestableContainer() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual TestableContainer& operator=(const TestableContainer& tc) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual TestableContainer& operator=(TestableContainer&& tc) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const TestableContainer& tc) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const TestableContainer& tc) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		virtual bool Exists(const Data& d) const noexcept = 0; // (concrete function should not throw exceptions)

	};

/* ************************************************************************** */

	template<typename Data>
	class DictionaryContainer : virtual public TestableContainer<Data> // Must extend TestableContainer<Data>
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~DictionaryContainer() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual DictionaryContainer& operator=(const DictionaryContainer& dc) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual DictionaryContainer& operator=(DictionaryContainer&& dc) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const DictionaryContainer& dc) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const DictionaryContainer& dc) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		virtual bool Insert(const Data& d) = 0; // Copy of the value
		virtual bool Insert(Data&& d) noexcept = 0; // Move of the value
		virtual bool Remove(const Data& d) = 0; // Override DictionaryContainer member

		virtual void Insert(const LinearContainer<Data>& lc);// Copy of the value
		virtual void Insert(LinearContainer<Data>&& lc) noexcept; // Move of the value
		virtual void Remove(const LinearContainer<Data>& lc); // Override DictionaryContainer member


	};

/* ************************************************************************** */

	template<typename Data>
	class MappableContainer : virtual public Container  // Must extend Container
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~MappableContainer() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual MappableContainer& operator=(const MappableContainer& mc) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual MappableContainer& operator=(MappableContainer&& mc) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const MappableContainer& mc) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const MappableContainer& mc) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		typedef std::function<void(Data&, void *)> MapFunctor;

		virtual void Map(MapFunctor, void *) = 0;

	};

/* ************************************************************************** */

	template<typename Data>
	class FoldableContainer : virtual public TestableContainer<Data>  // Must extend TestableContainer<Data>
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~FoldableContainer() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual FoldableContainer& operator=(const FoldableContainer& fc) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual FoldableContainer& operator=(FoldableContainer&& fc) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const FoldableContainer& fc) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const FoldableContainer& fc) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		typedef std::function<void(const Data&, const void *, void *)> FoldFunctor;

		virtual void Fold(FoldFunctor, const void *, void *) const = 0;

		/* ************************************************************************ */

		// Specific member functions (inherited from TestableContainer)

		virtual bool Exists(const Data& d) const noexcept override;

	};

/* ************************************************************************** */

	template<typename Data>
	class PreOrderMappableContainer : virtual public MappableContainer<Data>  // Must extend MappableContainer<Data>
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~PreOrderMappableContainer() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual PreOrderMappableContainer& operator=(const PreOrderMappableContainer& pomc) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual PreOrderMappableContainer& operator=(PreOrderMappableContainer&& pomc) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const PreOrderMappableContainer& pomc) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const PreOrderMappableContainer& pomc) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		using typename MappableContainer<Data>::MapFunctor;

		virtual void MapPreOrder(MapFunctor, void *) = 0;

		/* ************************************************************************ */

		// Specific member functions (inherited from MappableContainer)

		virtual void Map(MapFunctor, void *) override;
	};

/* ************************************************************************** */

	template<typename Data>
	class PreOrderFoldableContainer : virtual public FoldableContainer<Data>  // Must extend FoldableContainer<Data>
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~PreOrderFoldableContainer() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual PreOrderFoldableContainer& operator=(const PreOrderFoldableContainer& pofc) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual PreOrderFoldableContainer& operator=(PreOrderFoldableContainer&& pofc) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const PreOrderFoldableContainer& pofc) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const PreOrderFoldableContainer& pofc) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		using typename FoldableContainer<Data>::FoldFunctor;

		virtual void FoldPreOrder(FoldFunctor, const void *, void *) const = 0;

		/* ************************************************************************ */

		// Specific member functions (inherited from FoldableContainer)

		virtual void Fold(FoldFunctor, const void *, void *) const override; // Override FoldableContainer member

	};

/* ************************************************************************** */

	template<typename Data>
	class PostOrderMappableContainer : virtual public MappableContainer<Data>  // Must extend MappableContainer<Data>
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~PostOrderMappableContainer() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual PostOrderMappableContainer& operator=(const PostOrderMappableContainer& pomc) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual PostOrderMappableContainer& operator=(PostOrderMappableContainer&& pomc) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const PostOrderMappableContainer& pomc) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const PostOrderMappableContainer& pomc) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		using typename MappableContainer<Data>::MapFunctor;

		virtual void MapPostOrder(MapFunctor, void *) = 0;

		/* ************************************************************************ */

		// Specific member functions (inherited from MappableContainer)

		virtual void Map(MapFunctor, void *) override; // Override MappableContainer member

	};

/* ************************************************************************** */

	template<typename Data>
	class PostOrderFoldableContainer : virtual public FoldableContainer<Data>  // Must extend FoldableContainer<Data>
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~PostOrderFoldableContainer() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual PostOrderFoldableContainer& operator=(const PostOrderFoldableContainer& pofc) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual PostOrderFoldableContainer& operator=(PostOrderFoldableContainer&& pofc) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const PostOrderFoldableContainer& pofc) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const PostOrderFoldableContainer& pofc) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		using typename FoldableContainer<Data>::FoldFunctor;

		virtual void FoldPostOrder(FoldFunctor, const void *, void *) const = 0;

		/* ************************************************************************ */

		// Specific member functions (inherited from FoldableContainer)

		virtual void Fold(FoldFunctor, const void *, void *) const override; // Override FoldableContainer member

	};

/* ************************************************************************** */

	template<typename Data>
	class InOrderMappableContainer : virtual public MappableContainer<Data>  // Must extend MappableContainer<Data>
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~InOrderMappableContainer() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual InOrderMappableContainer& operator=(const InOrderMappableContainer& iomc) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual InOrderMappableContainer& operator=(InOrderMappableContainer&& iomc) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const InOrderMappableContainer& iomc) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const InOrderMappableContainer& iomc) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		using typename MappableContainer<Data>::MapFunctor;

		virtual void MapInOrder(MapFunctor, void *) = 0;

		/* ************************************************************************ */

		// Specific member functions (inherited from MappableContainer)

		virtual void Map(MapFunctor, void *) override; // Override MappableContainer member

	};

/* ************************************************************************** */

	template<typename Data>
	class InOrderFoldableContainer : virtual public FoldableContainer<Data>  // Must extend FoldableContainer<Data>
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~InOrderFoldableContainer() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual InOrderFoldableContainer& operator=(const InOrderFoldableContainer& iofc) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual InOrderFoldableContainer& operator=(InOrderFoldableContainer&& iofc) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const InOrderFoldableContainer& iofc) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const InOrderFoldableContainer& iofc) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		using typename FoldableContainer<Data>::FoldFunctor;

		virtual void FoldInOrder(FoldFunctor, const void *, void *) const = 0;

		/* ************************************************************************ */

		// Specific member functions (inherited from FoldableContainer)

		virtual void Fold(FoldFunctor, const void *, void *) const override; // Override FoldableContainer member

	};

/* ************************************************************************** */

	template<typename Data>
	class BreadthMappableContainer : virtual public MappableContainer<Data>   // Must extend MappableContainer<Data>
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~BreadthMappableContainer() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual BreadthMappableContainer& operator=(const BreadthMappableContainer& bmc) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual BreadthMappableContainer& operator=(BreadthMappableContainer&& bmc) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const BreadthMappableContainer& bmc) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const BreadthMappableContainer& bmc) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		using typename MappableContainer<Data>::MapFunctor;

		virtual void MapBreadth(MapFunctor, void *) = 0;

		/* ************************************************************************ */

		// Specific member functions (inherited from MappableContainer)

		virtual void Map(MapFunctor, void *) override; // Override MappableContainer member

	};

/* ************************************************************************** */

	template<typename Data>
	class BreadthFoldableContainer : virtual public FoldableContainer<Data>  // Must extend FoldableContainer<Data>
	{

	private:

		// ...

	protected:

		// ...

	public:

		// Destructor
		virtual ~BreadthFoldableContainer() = default;

		/* ************************************************************************ */

		// Copy assignment
		virtual BreadthFoldableContainer& operator=(const BreadthFoldableContainer& bfc) = delete; // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual BreadthFoldableContainer& operator=(BreadthFoldableContainer&& bfc) = delete; // Move assignment of abstract types should not be possible.

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const BreadthFoldableContainer& bfc) const noexcept = delete; // Comparison of abstract types might not be possible.
		virtual bool operator!=(const BreadthFoldableContainer& bfc) const noexcept = delete; // Comparison of abstract types might not be possible.

		/* ************************************************************************ */

		// Specific member functions

		using typename FoldableContainer<Data>::FoldFunctor;

		virtual void FoldBreadth(FoldFunctor, const void *, void *) const = 0;

		/* ************************************************************************ */

		// Specific member functions (inherited from FoldableContainer)

		virtual void Fold(FoldFunctor, const void *, void *) const override; // Override FoldableContainer member

	};

/* ************************************************************************** */

}

#include "container.cpp"

#endif
