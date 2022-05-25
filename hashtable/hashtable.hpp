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
		unsigned long operator()(const Data& d) const noexcept
		{
			void *v = (void *)&d;
			size_t j = sizeof(d);
			std::string s = "";
			for (size_t k = 0; k < j; k++)
			{
				s += (((char *)v)[k]);
			}
			return operator()(s);
		}
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
		Hash<Data> hash{};
		unsigned long a;
		unsigned long b;
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

	protected:

		// Auxiliary member functions

		unsigned long HashKey(const Data& d)
		{
			return hash(d);
		}

		// Copy assignment

		virtual HashTable& operator=(const HashTable& ht) // Copy assignment of abstract types should not be possible.
		{
			size = ht.size;
			a = ht.a;
			b = ht.b;
		}

		// Move assignment
		virtual HashTable& operator=(HashTable&& ht) noexcept // Move assignment of abstract types should not be possible.
		{
			size = std::move(ht.size);
			a = std::move(ht.a);
			b = std::move(ht.b);
		}

	};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
