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
		Vector<Data> table{};
		// ...

	public:

		// Default constructor
		HashTableOpnAdr() = default;

		/* ************************************************************************ */

		// Specific constructors
		HashTableOpnAdr(unsigned long s) // A hash table of a given size
		{
			table.Resize(s);
		}
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
		HashTableOpnAdr& operator=(const HashTableOpnAdr& ht);

		// Move assignment
		HashTableOpnAdr& operator=(HashTableOpnAdr&& ht) noexcept;

		/* ************************************************************************ */

		// Comparison operators
		bool operator==(const HashTableOpnAdr& ht) const noexcept;
		bool operator!=(const HashTableOpnAdr& ht) const noexcept;

		/* ************************************************************************ */

		// Specific member functions (inherited from HashTable)

		void Resize(unsigned long s) override // Resize the hashtable to a given size
		{

		}

		/* ************************************************************************ */

		// Specific member functions (inherited from DictionaryContainer)

		bool Insert(const Data& d) // Override DictionaryContainer member (Copy of the value)
		{
			if(table[HashKey(d)])
			{
				size++;
				return true;
			}
			return false;
		}
		bool Insert(Data&& d) // Override DictionaryContainer member (Move of the value)
		{
			if(table[HashKey(d)])
			{
				size++;
				return true;
			}
			return false;
		}
		bool Remove(const Data& d) // Override DictionaryContainer member
		{
			if(table[HashKey(d)])
			{
				size--;
				return true;
			}
			return false;
		}
		void Insert(const LinearContainer<Data>& lc)
		{
			DictionaryContainer<Data>::Insert(lc);
		};
		void Insert(LinearContainer<Data>&& lc)
		{
			DictionaryContainer<Data>::Insert(std::move(lc));
		};
		void Remove(const LinearContainer<Data>& lc)
		{
			DictionaryContainer<Data>::Remove(lc);
		};
		/* ************************************************************************ */

		// Specific member functions (inherited from TestableContainer)

		bool Exists(const Data& d) // Override TestableContainer member
		{
			return table.Exists(d);
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from MappableContainer)

		using typename MappableContainer<Data>::MapFunctor;

		void Map(MapFunctor f, void *par) override // Override MappableContainer member
		{/*
			for(unsigned long i = 0 ; i < table.Size() ; i++)
			{
				if(!table[i].Empty)
					table[i].Map(f,par);
			}*/
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from FoldableContainer)

		using typename FoldableContainer<Data>::FoldFunctor;

		void Fold(FoldFunctor f, const void *par, void *acc) const override // Override FoldableContainer member
		{/*
			for(unsigned long i = 0 ; i < table.Size() ; i++)
			{
				if(!table[i].Empty)
					table[i].Fold(f,par,acc);
			}*/
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from Container)

		void Clear() noexcept // Override Container member
		{
			table.Clear();
			size = 0;
		}

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
