#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
// #include ...

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

	template<typename Data>
	class HashTableOpnAdr : virtual public HashTable<Data>
	{ // Must extend HashTable<Data>

	private:

		// ...

	protected:

		using HashTable<Data>::size;
		using HashTable<Data>::a;
		using HashTable<Data>::b;
		using HashTable<Data>::p;
		using HashTable<Data>>::hash;
		Vector<Data> table;
		// ...

	public:

		// Default constructor
		// HashTableOpnAdr() specifiers;

		/* ************************************************************************ */

		// Specific constructors
		HashTableOpnAdr(unsigned long s); // A hash table of a given size
		HashTableOpnAdr(const LinearContainer<Data>& lc); // A hash table obtained from a LinearContainer
		HashTableOpnAdr(unsigned long s, const LinearContainer<Data>& ls); // A hash table of a given size obtained from a LinearContainer

		/* ************************************************************************ */

		// Copy constructor
		HashTableOpnAdr(const HashTableOpnAdr& ht);

		// Move constructor
		HashTableOpnAdr(HashTableOpnAdr&& ht) noexcept;

		/* ************************************************************************ */

		// Destructor
		virtual ~HashTableOpnAdr();

		/* ************************************************************************ */

		// Copy assignment
		// type operator=(argument) specifiers;

		// Move assignment
		// type operator=(argument) specifiers;

		/* ************************************************************************ */

		// Comparison operators
		virtual bool operator==(const HashTableOpnAdr& ht) const noexcept;
		virtual bool operator!=(const HashTableOpnAdr& ht) const noexcept;

		/* ************************************************************************ */

		// Specific member functions (inherited from HashTable)

		void Resize(unsigned long s) override // Resize the hashtable to a given size
		{

		}

		/* ************************************************************************ */

		// Specific member functions (inherited from DictionaryContainer)

		bool Insert(const Data& d) // Override DictionaryContainer member (Copy of the value)
		{

		}
		bool Insert(Data&& d) // Override DictionaryContainer member (Move of the value)
		{

		}
		bool Remove(const Data& d) // Override DictionaryContainer member
		{

		}
		/* ************************************************************************ */

		// Specific member functions (inherited from TestableContainer)

		bool Exists(const Data& d) // Override TestableContainer member
		{

		}

		/* ************************************************************************ */

		// Specific member functions (inherited from MappableContainer)

		// type Map(argument) specifiers; // Override MappableContainer member

		/* ************************************************************************ */

		// Specific member functions (inherited from FoldableContainer)

		// type Fold(argument) specifiers; // Override FoldableContainer member

		/* ************************************************************************ */

		// Specific member functions (inherited from Container)

		// type Clear() specifiers; // Override Container member

	public:

		// Auxiliary member functions

		// type Find(argument) specifiers;
		// type FindEmpty(argument) specifiers;
		// type Remove(argument) specifiers;

	};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
