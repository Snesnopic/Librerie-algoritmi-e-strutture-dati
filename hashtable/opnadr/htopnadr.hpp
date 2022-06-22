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
		using HashTable<Data>::hash;
		using HashTable<Data>::HashKey;
		using DictionaryContainer<Data>::Insert;
		using DictionaryContainer<Data>::Remove;
		Vector<Data *> table{};
		Vector<bool> deleted{};

		// Hash function
		virtual unsigned long HashKey(const Data& d) const override;

	public:

		// Default constructor
		HashTableOpnAdr() : HashTableOpnAdr(127) {}

		/* ************************************************************************ */

		// Specific constructors
		explicit HashTableOpnAdr(unsigned long s); // A hash table of a given size

		explicit HashTableOpnAdr(const LinearContainer<Data>& lc); // A hash table obtained from a LinearContainer

		HashTableOpnAdr(unsigned long s, const LinearContainer<Data>& lc);// A hash table of a given size obtained from a LinearContainer


		/* ************************************************************************ */

		// Copy constructor
		HashTableOpnAdr(const HashTableOpnAdr& ht);

		// Move constructor
		HashTableOpnAdr(HashTableOpnAdr&& ht) noexcept;

		/* ************************************************************************ */

		// Destructor
		virtual ~HashTableOpnAdr() override;

		/* ************************************************************************ */

		// Copy assignment
		HashTableOpnAdr& operator=(const HashTableOpnAdr& ht);

		// Move assignment
		HashTableOpnAdr& operator=(HashTableOpnAdr&& ht) noexcept;

		/* ************************************************************************ */

		// Comparison operators
		bool operator==(const HashTableOpnAdr& ht) const noexcept;

		bool operator!=(const HashTableOpnAdr& ht) const noexcept;

		/* ************************************************************************ */

		// Specific member functions (inherited from HashTable)

		void Resize(unsigned long s) override; // Resize the hashtable to a given size

		/* ************************************************************************ */

		// Specific member functions (inherited from DictionaryContainer)

		bool Insert(const Data& d) override; // Override DictionaryContainer member (Copy of the value)
		bool Insert(Data&& d) noexcept override; // Override DictionaryContainer member (Move of the value)
		bool Remove(const Data& d) override; // Override DictionaryContainer member

		/* ************************************************************************ */

		// Specific member functions (inherited from TestableContainer)

		bool Exists(const Data& d) const noexcept override; // Override TestableContainer member

		/* ************************************************************************ */

		// Specific member functions (inherited from MappableContainer)

		using typename MappableContainer<Data>::MapFunctor;

		void Map(MapFunctor f, void *par) override; // Override MappableContainer member

		/* ************************************************************************ */

		// Specific member functions (inherited from FoldableContainer)

		using typename FoldableContainer<Data>::FoldFunctor;

		void Fold(FoldFunctor f, const void *par, void *acc) const override;// Override FoldableContainer member

		/* ************************************************************************ */

		// Specific member functions (inherited from Container)

		void Clear() noexcept override; // Override Container member

	};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
