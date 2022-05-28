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
		unsigned long operator()(const Data& d) const noexcept;/*
		{
			void *v = (void *)&d;
			size_t j = sizeof(d);
			std::string s = "";
			for (size_t k = 0; k < j; k++)
			{
				s += (((char *)v)[k]);
			}
			return operator()(s);
		}*/
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
		unsigned long a{};
		unsigned long b{};
		const unsigned long p = 34019;
		// ...

	public:

		// Constructor
		HashTable()
		{
			std::default_random_engine gen(std::random_device{}());
			std::uniform_int_distribution<unsigned long> dista(1, p);
			while (true)
			{
				a = dista(gen);
				if (a <= 1)
					continue;
				if (a <= 3)
					break;
				unsigned long range = sqrt(a);
				if (a % 2 == 0 || a % 3 == 0)
					continue;
				for (unsigned long i = 5; i <= range; i += 6)
				{
					if (a % i == 0 || a % (i + 2) == 0)
						continue;
				}
				break;
			}
			std::uniform_int_distribution<unsigned long> distb(0, a - 1);
			while (true)
			{
				b = distb(gen);
				if (b <= 1)
					continue;
				if (b <= 3)
					break;
				unsigned long range = sqrt(b);
				if (b % 2 == 0 || b % 3 == 0)
					continue;
				for (unsigned long i = 5; i <= b; i += 6)
				{
					if (b % i == 0 || b % (i + 2) == 0)
						continue;
				}
				break;
			}
		}

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

		virtual unsigned long HashKey(const Data& d) const = 0;

		// Copy assignment

		virtual HashTable& operator=(const HashTable& ht) // Copy assignment of abstract types should not be possible.
		{
			a = ht.a;
			b = ht.b;
			return *this;
		}

		// Move assignment
		virtual HashTable& operator=(HashTable&& ht) noexcept // Move assignment of abstract types should not be possible.
		{
			size = std::move(ht.size);
			a = std::move(ht.a);
			b = std::move(ht.b);
			return *this;
		}

	};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
