namespace lasd
{

/* ************************************************************************** */
	template<typename Data>
	unsigned long HashTableClsAdr<Data>::HashKey(const Data& d) const // Hash function
	{
		return (((a * hash(d)) + b) % p) % table.Size();
	}

	template<typename Data>
	HashTableClsAdr<Data>::HashTableClsAdr(unsigned long s)
	{
		table.Resize(s);
	}

	template<typename Data>
	HashTableClsAdr<Data>::HashTableClsAdr(unsigned long s, const LinearContainer<Data>& lc) // A hash table of a given size obtained from a LinearContainer
	{
		table.Resize(s);
		Insert(lc);
	}

	// Copy constructor
	template<typename Data>
	HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr& ht)
	{
		HashTable<Data>::operator=(ht);
		size = ht.size;
		table = ht.table;
	}

	// Move constructor
	template<typename Data>
	HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr&& ht) noexcept
	{
		HashTable<Data>::operator=(std::move(ht));
		table = std::move(ht.table);
	}

	// Destructor
	template<typename Data>
	HashTableClsAdr<Data>::~HashTableClsAdr()
	{
		table.Clear();
	}

	// Copy assignment
	template<typename Data>
	HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr& ht)
	{
		if (*this != ht)
		{
			HashTable<Data>::operator=(ht);
			size = ht.size;
			table = ht.table;
		}
		return *this;
	}

	// Move assignment
	template<typename Data>
	HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr&& ht) noexcept
	{
		if (*this != ht)
		{
			HashTable<Data>::operator=(std::move(ht));
			table = std::move(ht.table);
		}
		return *this;
	}

	// Comparison operators
	template<typename Data>
	bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr& ht) const noexcept
	{
		if (size == ht.size)
		{
			BST<Data> bst1;
			for (unsigned long i = 0; i < table.Size(); i++)
			{
				BTInOrderIterator<Data> j(table[i]);
				while (!j.Terminated())
				{
					bst1.Insert(*j);
					++j;
				}
			}
			BST<Data> bst2;
			for (unsigned long i = 0; i < ht.table.Size(); i++)
			{
				BTInOrderIterator<Data> j(ht.table[i]);
				while (!j.Terminated())
				{
					bst2.Insert(*j);
					++j;
				}
			}
			return bst1 == bst2;
		}
		return false;
	}

	template<typename Data>
	bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr& ht) const noexcept
	{
		return !(*this == ht);
	}

	// Specific member functions (inherited from HashTable)
	template<typename Data>
	void HashTableClsAdr<Data>::Resize(const unsigned long newSize) // Resize the hashtable to a given size
	{
		HashTableClsAdr<Data> newHash(newSize);
		for (unsigned long i = 0; i < table.Size(); i++)
		{
			if (table[i].Empty())
				continue;
			else
			{
				BTInOrderIterator<Data> j(table[i]);
				while (!j.Terminated())
				{
					newHash.Insert(*j);
					++j;
				}
				table[i].Clear();
			}
		}
		table.Clear();
		std::swap(*this, newHash);
	}

	// Specific member functions (inherited from DictionaryContainer)
	template<typename Data>
	bool HashTableClsAdr<Data>::Insert(const Data& d) // Override DictionaryContainer member (Copy of the value)
	{
		if (table[HashKey(d)].Insert(d))
		{
			size++;
			return true;
		}
		return false;
	}

	template<typename Data>
	bool HashTableClsAdr<Data>::Insert(Data&& d) noexcept // Override DictionaryContainer member (Move of the value)
	{
		if (table[HashKey(d)].Insert(std::move(d)))
		{
			size++;
			return true;
		}
		return false;
	}

	template<typename Data>
	bool HashTableClsAdr<Data>::Remove(const Data& d) // Override DictionaryContainer member
	{
		if(table[HashKey(d)].Remove(d))
		{
			size--;
			return true;
		}
		return false;
	}

	// Specific member functions (inherited from TestableContainer)
	template<typename Data>
	bool HashTableClsAdr<Data>::Exists(const Data& d) const noexcept // Override TestableContainer member
	{
		if(table[HashKey(d)].Exists(d))
			return true;
		return false;
	}

	// Specific member functions (inherited from MappableContainer)
	template<typename Data>
	void HashTableClsAdr<Data>::Map(MapFunctor f, void *par) // Override MappableContainer member
	{
		for (unsigned long i = 0; i < table.Size(); i++)
		{
			if (!table[i].Empty())
				table[i].Map(f, par);
		}
	}

	// Specific member functions (inherited from FoldableContainer)
	template<typename Data>
	void HashTableClsAdr<Data>::Fold(FoldFunctor f, const void *par, void *acc) const // Override FoldableContainer member
	{
		for (unsigned long i = 0; i < table.Size(); i++)
		{
			if (!table[i].Empty())
				table[i].Fold(f, par, acc);
		}
	}

	// Specific member functions (inherited from Container)
	template<typename Data>
	void HashTableClsAdr<Data>::Clear() noexcept // Override Container member
	{
		table.Clear();
		table.Resize(127);
		size = 0;
	}

/* ************************************************************************** */

}