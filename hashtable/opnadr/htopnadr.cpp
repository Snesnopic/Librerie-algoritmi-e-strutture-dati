namespace lasd
{

/* ************************************************************************** */
	template<typename Data>
	unsigned long HashTableOpnAdr<Data>::HashKey(const Data& d) const // Hash function
	{
		return (((a * hash(d)) + b) % p) % table.Size();
	}

	template<typename Data>
	HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long s) // A hash table of a given size
	{
		table.Resize(s);
		deleted.Resize(s);
		for (unsigned long i = 0; i < s; i++)
		{
			table[i] = nullptr;
			deleted[i] = false;
		}
	}

	template<typename Data>
	HashTableOpnAdr<Data>::HashTableOpnAdr(const LinearContainer<Data>& lc) // A hash table obtained from a LinearContainer
	{
		unsigned long s = 127;
		if (s < lc.Size())
			s = lc.Size();
		table.Resize(s);
		deleted.Resize(s);
		for (unsigned long i = 0; i < s; i++)
		{
			table[i] = nullptr;
			deleted[i] = false;
		}
		Insert(lc);
	}

	template<typename Data>
	HashTableOpnAdr<Data>::HashTableOpnAdr(unsigned long s, const LinearContainer<Data>& lc)// A hash table of a given size obtained from a LinearContainer
	{
		if (s < lc.Size())
			s = lc.Size();
		table.Resize(s);
		deleted.Resize(s);
		for (unsigned long i = 0; i < s; i++)
		{
			table[i] = nullptr;
			deleted[i] = false;
		}
		Insert(lc);
	}

	// Copy constructor
	template<typename Data>
	HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr& ht)
	{
		HashTable<Data>::operator=(ht);
		for (unsigned long i = 0; i < ht.table.Size(); i++)
		{
			if (ht.table[i] != nullptr && !ht.deleted[i])
				Insert(*(ht.table[i]));
		}
	}

	// Move constructor
	template<typename Data>
	HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr&& ht) noexcept
	{
		HashTable<Data>::operator=(std::move(ht));
		table = std::move(ht.table);
		deleted = std::move(ht.deleted);
		ht.Clear();
	}

	// Destructor
	template<typename Data>
	HashTableOpnAdr<Data>::~HashTableOpnAdr()
	{
		Clear();
	}

	// Copy assignment
	template<typename Data>
	HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr& ht)
	{
		HashTable<Data>::operator=(ht);
		for (unsigned long i = 0; i < ht.table.Size(); i++)
		{
			if (ht.table[i] != nullptr && !ht.deleted[i])
				Insert(*(ht.table[i]));
		}
		return *this;
	}

	// Move assignment
	template<typename Data>
	HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr&& ht) noexcept
	{
		HashTable<Data>::operator=(std::move(ht));
		table = std::move(ht.table);
		deleted = std::move(ht.deleted);
		ht.Clear();
		return *this;
	}

	// Comparison operators
	template<typename Data>
	bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr& ht) const noexcept
	{
		if (size == ht.size)
		{
			for (unsigned long i = 0; i < table.Size(); i++)
			{
				if (table[i] != nullptr && !deleted[i])
				{
					if (!ht.Exists(*table[i]))
						return false;
				}
			}
			return true;
		}
		return false;
	}

	template<typename Data>
	bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr& ht) const noexcept
	{
		return !(*this == ht);
	}

	// Specific member functions (inherited from HashTable)
	template<typename Data>
	void HashTableOpnAdr<Data>::Resize(unsigned long s)  // Resize the hashtable to a given size
	{
		if (s >= size)        //>= perché compiendo una Resize su una Hash con la stessa size di prima possiamo rimuovere i valori contrassegnati 'eliminati'
		{
			HashTableOpnAdr newHash(s);
			for (unsigned long i = 0; i < table.Size(); i++)
			{
				if (table[i] != nullptr && !deleted[i])
				{
					newHash.Insert(*table[i]);
				}
			}
			*this = std::move(newHash);
		}
	}

	// Specific member functions (inherited from DictionaryContainer)
	template<typename Data>
	bool HashTableOpnAdr<Data>::Insert(const Data& d) // Override DictionaryContainer member (Copy of the value)
	{
		if (size >= table.Size() / 2)
			Resize((table.Size() * 2) + 1);
		unsigned long j = HashKey(d);
		for (unsigned long i = 0; i < table.Size(); i++)
		{
			unsigned long index = (j + i) % table.Size();
			if (table[index] != nullptr)
			{
				if (*table[index] == d)
				{
					if (deleted[index])
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

	template<typename Data>
	bool HashTableOpnAdr<Data>::Insert(Data&& d) noexcept// Override DictionaryContainer member (Move of the value)
	{
		if (size >= table.Size() / 2)
			Resize((table.Size() * 2) + 1);
		unsigned long j = HashKey(d);
		for (unsigned long i = 0; i < table.Size(); i++)
		{
			unsigned long index = (j + i) % table.Size();
			if (table[index] != nullptr)
			{
				if (*table[index] == d)
				{
					if (deleted[index])
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

	template<typename Data>
	bool HashTableOpnAdr<Data>::Remove(const Data& d) // Override DictionaryContainer member
	{
		unsigned long j = HashKey(d);
		for (unsigned long i = 0; i < table.Size(); i++)
		{
			unsigned long index = (j + i) % table.Size();
			if (table[index] == nullptr)
				return false;
			if (*(table[index]) == d && !deleted[index])
			{
				size--;
				deleted[index] = true;
				return true;
			}
		}
		return false;
	}

	// Specific member functions (inherited from TestableContainer)
	template<typename Data>
	bool HashTableOpnAdr<Data>::Exists(const Data& d) const noexcept  // Override TestableContainer member
	{
		unsigned long j = HashKey(d);
		for (unsigned long i = 0; i < table.Size(); i++)
		{
			unsigned long index = (j + i) % table.Size();
			if (table[index] == nullptr)
				return false;
			if (*(table[index]) == d && !deleted[index])
				return true;
		}
		return false;
	}

	// Specific member functions (inherited from MappableContainer)
	template<typename Data>
	void HashTableOpnAdr<Data>::Map(MapFunctor f, void *par) // Override MappableContainer member
	{
		for (unsigned long i = 0; i < table.Size(); i++)
		{
			if (table[i] != nullptr && !deleted[i])
				f(*table[i], par);
		}
	}

	// Specific member functions (inherited from FoldableContainer)
	template<typename Data>
	void HashTableOpnAdr<Data>::Fold(FoldFunctor f, const void *par, void *acc) const // Override FoldableContainer member
	{
		for (unsigned long i = 0; i < table.Size(); i++)
		{
			if (table[i] != nullptr && !deleted[i])
				f(*table[i], par, acc);
		}
	}

	// Specific member functions (inherited from Container)
	template<typename Data>
	void HashTableOpnAdr<Data>::Clear() noexcept // Override Container member
	{
		for (unsigned long i = 0; i < table.Size(); i++)
		{
			if (table[i] != nullptr)
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
/* ************************************************************************** */

}
