#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */


#include "../hashtable.hpp"
#include "../../bst/bst.hpp"

/* ************************************************************************** */

namespace lasd
{

/* ************************************************************************** */

	template<typename Data>
	class HashTableClsAdr : virtual public HashTable<Data>
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
		Vector<BST<Data>> table{};
		// ...

	public:

		// Default constructor
		HashTableClsAdr() = default;

		/* ************************************************************************ */

		// Specific constructors
		HashTableClsAdr(unsigned long s) // A hash table of a given size
		{
			table.Resize(s);
		}
		HashTableClsAdr(const LinearContainer<Data>& lc) : HashTableClsAdr(lc.Size())// A hash table obtained from a LinearContainer
		{
			size = lc.Size();
			Insert(lc);
		}
		HashTableClsAdr(unsigned long s, const LinearContainer<Data>& lc) : HashTableClsAdr(s)// A hash table of a given size obtained from a LinearContainer
		{
			size = lc.Size();
			Insert(lc);
		}

		/* ************************************************************************ */

		// Copy constructor
		HashTableClsAdr(const HashTableClsAdr& ht)
		{
			HashTable<Data>::operator=(ht);
			table = ht.table;
		}

		// Move constructor
		HashTableClsAdr(HashTableClsAdr&& ht) noexcept
		{
			HashTable<Data>::operator=(std::move(ht));
			table = std::move(ht.table);
		}

		/* ************************************************************************ */

		// Destructor
		virtual ~HashTableClsAdr()
		{
			table.Clear();
		}

		/* ************************************************************************ */

		// Copy assignment
		HashTableClsAdr& operator=(const HashTableClsAdr& ht)
		{
			if(*this != ht)
			{
				HashTable<Data>::operator=(ht);
				table = ht.table;
			}
			return *this;
		}

		// Move assignment
		HashTableClsAdr& operator=(HashTableClsAdr&& ht) noexcept
		{
			if(*this != ht)
			{
				HashTable<Data>::operator=(std::move(ht));
				table = std::move(ht.table);
			}
			return *this;
		}

		/* ************************************************************************ */

		// Comparison operators
		bool operator==(const HashTableClsAdr& ht) const noexcept
		{
			if(size == ht.size)
			{
				BST<Data> bst1;
				for(unsigned long i = 0;i < table.Size();i++)
				{
					BTInOrderIterator<Data> j(table[i]);
					while(!j.Terminated())
					{
						bst1.Insert(*j);
						++j;
					}
				}
				BST<Data> bst2;
				for(unsigned long i = 0;i < ht.table.Size();i++)
				{
					BTInOrderIterator<Data> j(ht.table[i]);
					while(!j.Terminated())
					{
						bst1.Insert(*j);
						++j;
					}
				}
				return bst1 == bst2;
			}
			return false;
		}
		bool operator!=(const HashTableClsAdr& ht) const noexcept
		{
			return !(*this == ht);
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from HashTable)

		void Resize(const unsigned long newSize) // Resize the hashtable to a given size
		{
			Vector<BST<Data>> newTable(newSize);
			for(unsigned long i = 0; i < table.Size();i++)
			{
				if(table[i].Empty())
					continue;
				else
				{
					BTInOrderIterator<Data> j(table[i]);
					while(!j.Terminated())
					{
						newTable[this->HashKey(*j)].Insert(*j);
						++j;
					}
					table[i].Clear();
				}
			}
			table.Clear();
			std::swap(table,newTable);
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from DictionaryContainer)

		bool Insert(const Data& d) // Override DictionaryContainer member (Copy of the value)
		{
			if(table[HashKey(d)].Insert(d))
			{
				size++;
				return true;
			}
			return false;
		}
		bool Insert(Data&& d) // Override DictionaryContainer member (Move of the value)
		{
			if(table[HashKey(d)].Insert(std::move(d)))
			{
				size++;
				return true;
			}
			return false;
		}
		bool Remove(const Data& d) // Override DictionaryContainer member
		{
			if(table[HashKey(d)].Remove(d))
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

		bool Exists(const Data& d) const noexcept // Override TestableContainer member
		{
			return table[HashKey(d)].Exists(d);
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from MappableContainer)

		using typename MappableContainer<Data>::MapFunctor;

		void Map(MapFunctor f, void *par) override // Override MappableContainer member
		{
			for(unsigned long i = 0 ; i < table.Size() ; i++)
			{
				if(!table[i].Empty())
					table[i].Map(f,par);
			}
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from FoldableContainer)

		using typename FoldableContainer<Data>::FoldFunctor;

		void Fold(FoldFunctor f, const void *par, void *acc) const override // Override FoldableContainer member
		{
			for(unsigned long i = 0 ; i < table.Size() ; i++)
			{
				if(!table[i].Empty())
					table[i].Fold(f,par,acc);
			}
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from Container)

		void Clear() noexcept // Override Container member
		{
			table.Clear();
			size = 0;
		}

	};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
