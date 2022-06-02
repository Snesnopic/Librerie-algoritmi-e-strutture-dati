#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

	template<typename Data>
	class Hash
	{

	public:
		unsigned long operator()(const Data& d) const noexcept;

	};

/* ************************************************************************** */

	template<typename Data>
	class HashTable : virtual public DictionaryContainer<Data>, virtual public MappableContainer<Data>, virtual public FoldableContainer<Data>
	{   // Must extend DictionaryContainer<Data>,
		//             MappableContainer<Data>,
		//             FoldableContainer<Data>

	private:

		// ...

	protected:

		using DictionaryContainer<Data>::size;
		const Hash<Data> hash{};
		short a{};
		short b{};
		const int p = 34019;
		// ...

	public:

		// Constructor
		HashTable();

		// Destructor
		virtual ~HashTable() = default;

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const HashTable& ht) const noexcept = delete; // Comparison of abstract binary tree is possible.
		virtual bool operator!=(const HashTable& ht) const noexcept = delete; // Comparison of abstract binary tree is possible.

		/* ************************************************************************ */

		// Specific member function

		virtual void Resize(unsigned long i) = 0; // Resize the hashtable to a given size



		// Auxiliary member functions
	protected:
		virtual unsigned long HashKey(const Data& d) const = 0;

		// Copy assignment
		virtual HashTable& operator=(const HashTable& ht); // Copy assignment of abstract types should not be possible.

		// Move assignment
		virtual HashTable& operator=(HashTable&& ht) noexcept; // Move assignment of abstract types should not be possible.

	};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
