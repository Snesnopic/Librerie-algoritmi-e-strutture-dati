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
		Vector<Data*> table{};
		Vector<bool> deleted{};
		// ...
        virtual unsigned long HashKey(const Data& d) const
        {
            return (((a*hash(d))+b)% p) % table.Size();
        }
	public:

		// Default constructor
		HashTableOpnAdr(): HashTableOpnAdr(127){};

		/* ************************************************************************ */

		// Specific constructors
		HashTableOpnAdr(unsigned long s) // A hash table of a given size
		{
			table.Resize(s);
			deleted.Resize(s);
			for(unsigned long i = 0 ; i < s ; i++)
			{
				table[i] = nullptr;
				deleted[i] = false;
			}
		}
		HashTableOpnAdr(const LinearContainer<Data>& lc): HashTableOpnAdr(lc.Size()) // A hash table obtained from a LinearContainer
		{
			Insert(lc);
		}
		HashTableOpnAdr(unsigned long s, const LinearContainer<Data>& lc)// A hash table of a given size obtained from a LinearContainer
		{
			if(s < lc.Size())
				s = lc.Size();
			table.Resize(s);
            deleted.Resize(s);
			for(unsigned long i = 0 ; i < s ; i++)
			{
				table[i] = nullptr;
				deleted[i] = false;
			}
			Insert(lc);
		}

		/* ************************************************************************ */

		// Copy constructor
		HashTableOpnAdr(const HashTableOpnAdr& ht) : HashTableOpnAdr(ht.size)
		{
			HashTable<Data>::operator=(ht);
            for(unsigned long i = 0; i < ht.table.Size() ; i++)
			{
				if(ht.table[i] != nullptr && !ht.deleted[i])
					Insert(*(ht.table[i]));
			}
		}

		// Move constructor
		HashTableOpnAdr(HashTableOpnAdr&& ht) noexcept : HashTableOpnAdr(ht.size)
		{
            HashTable<Data>::operator=(std::move(ht));
            table = std::move(ht.table);
            deleted = std::move(ht.deleted);
            ht.Clear();
		}

		/* ************************************************************************ */

		// Destructor
		virtual ~HashTableOpnAdr()
		{
			Clear();
		}

		/* ************************************************************************ */

		// Copy assignment
		HashTableOpnAdr& operator=(const HashTableOpnAdr& ht)
		{
            HashTable<Data>::operator=(ht);
            for(unsigned long i = 0; i < ht.table.Size() ; i++)
            {
                if(ht.table[i] != nullptr && !ht.deleted[i])
                    Insert(*(ht.table[i]));
            }
            return *this;
		}

		// Move assignment
		HashTableOpnAdr& operator=(HashTableOpnAdr&& ht) noexcept
		{
            HashTable<Data>::operator=(std::move(ht));
            table = std::move(ht.table);
            deleted = std::move(ht.deleted);
            ht.Clear();
			return *this;
		}

		/* ************************************************************************ */

		// Comparison operators
		bool operator==(const HashTableOpnAdr& ht) const noexcept
		{
			if(size == ht.size)
			{
				for(unsigned long i = 0; i < table.Size() ; i++)
				{
					if(table[i] != nullptr && !deleted[i])
					{
						if(!ht.Exists(*table[i]))
							return false;
					}
				}
				return true;
			}
			return false;
		}
		bool operator!=(const HashTableOpnAdr& ht) const noexcept
		{
			return !(*this == ht);
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from HashTable)

		void Resize(unsigned long s) override // Resize the hashtable to a given size
		{
			if(s >= size)		//>= perché compiendo una Resize su una Hash con la stessa size di prima possiamo rimuovere i valori contrassegnati 'eliminati'
			{
				HashTableOpnAdr newHash(s);
				for(unsigned long i = 0; i < table.Size(); i++)
				{
					if(table[i] != nullptr && !deleted[i])
					{
						newHash.Insert(*table[i]);
					}
				}
				*this = std::move(newHash);
            }
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from DictionaryContainer)

		bool Insert(const Data& d) // Override DictionaryContainer member (Copy of the value)
		{
            if(size == table.Size())
                Resize((table.Size()*2)+1);
            unsigned long j = HashKey(d);
            for(unsigned long i = 0; i < table.Size(); i++)
            {
                unsigned long index = (j+i)%table.Size();
                if(table[index] != nullptr)
                {
                    if(*table[index] == d)
                    {
                        if(deleted[index])
                        {
                            size++;
                            deleted[index] = false;
                            return true;
                        }
                        return false;
                    }
                }
                else
                {
                    table[index] = new Data(d);
                    size++;
                    deleted[index] = false;
                    return true;
                }
            }
            return false;
		}
		bool Insert(Data&& d) // Override DictionaryContainer member (Move of the value)
		{
            if(size == table.Size())
                Resize((table.Size()*2)+1);
            unsigned long j = HashKey(d);
            for(unsigned long i = 0; i < table.Size(); i++)
            {
                unsigned long index = (j+i)%table.Size();
                if(table[index] != nullptr)
                {
                    if(*table[index] == d)
                    {
                        if(deleted[index])
                        {
                            size++;
                            deleted[index] = false;
                            return true;
                        }
                        return false;
                    }
                }
                else
                {
                    table[index] = new Data(std::move(d));
                    size++;
                    deleted[index] = false;
                    return true;
                }
            }
            return false;
        }
		bool Remove(const Data& d) // Override DictionaryContainer member
		{
			unsigned long j = HashKey(d);
			for(unsigned long i = 0; i < table.Size(); i++)
			{
                unsigned long index = (j+i)%table.Size();
                if(table[index] == nullptr)
                    return false;
				if(*(table[index]) == d && !deleted[index])
				{
					size--;
					deleted[index] = true;
					return true;
				}
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

		bool Exists(const Data& d) const noexcept override // Override TestableContainer member
		{
			unsigned long j = HashKey(d);
			for(unsigned long i = 0; i < table.Size(); i++)
			{
                unsigned long index = (j+i)%table.Size();
                if(table[index] == nullptr)
                    return false;
				if(*(table[index]) == d && !deleted[index])
					return true;
			}
			return false;
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from MappableContainer)

		using typename MappableContainer<Data>::MapFunctor;

		void Map(MapFunctor f, void *par) override // Override MappableContainer member
		{
			for(unsigned long i = 0 ; i < table.Size() ; i++)
			{
				if(table[i] != nullptr && !deleted[i])
					f(*table[i],par);
			}
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from FoldableContainer)

		using typename FoldableContainer<Data>::FoldFunctor;

		void Fold(FoldFunctor f, const void *par, void *acc) const override // Override FoldableContainer member
		{
			for(unsigned long i = 0 ; i < table.Size() ; i++)
			{
				if(table[i] != nullptr && !deleted[i])
					f(*table[i],par,acc);
			}
		}

		/* ************************************************************************ */

		// Specific member functions (inherited from Container)

		void Clear() noexcept // Override Container member
		{
            for(unsigned long i = 0 ; i < table.Size() ; i++)
            {
                if(table[i] != nullptr)
                {
                    delete table[i];
                    table[i] = nullptr;
                }
            }
			table.Clear();
			deleted.Clear();
            table.Resize(1);
            table[0] = nullptr;
            deleted.Resize(1);
            deleted[0] = false;
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
