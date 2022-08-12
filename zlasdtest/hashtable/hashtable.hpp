#ifndef HASHTABLETEST_HPP
#define HASHTABLETEST_HPP

#include "../../hashtable/hashtable.hpp"

/* ************************************************************************** */

template<typename HT>
void EqualHT(unsigned int& testnum, unsigned int& testerr, const HT& ht1, const HT& ht2)
{
	testnum++;
	bool tst;
	try
	{
		std::cout << " " << testnum << " (" << testerr << ") The two hash tables are " << ((tst = (ht1 == ht2)) ? "" : "not ") << "equal: ";
		std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
	}
	catch (std::exception& exc)
	{
		std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
	}
	testerr += (1 - static_cast<unsigned int>(tst));
}

template<typename HT>
void NonEqualHT(unsigned int& testnum, unsigned int& testerr, const HT& ht1, const HT& ht2)
{
	testnum++;
	bool tst;
	try
	{
		std::cout << " " << testnum << " (" << testerr << ") The two hash tables are " << ((tst = (ht1 != ht2)) ? "not " : "") << "equal: ";
		std::cout << (tst ? "Correct" : "Error") << "!" << std::endl;
	}
	catch (std::exception& exc)
	{
		std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
	}
	testerr += (1 - static_cast<unsigned int>(tst));
}

/* ************************************************************************** */

template<typename Data>
void CountHT(unsigned int& testnum, unsigned int& testerr, const lasd::HashTable<Data>& ht, const lasd::LinearContainer<Data>& con, unsigned int num)
{
	testnum++;
	bool tst;
	try
	{
		unsigned int cnt = 0;
		for (unsigned int i = 0; i < con.Size(); ++i)
		{
			if (ht.Exists(con[i]))
			{
				++cnt;
			}
		}
		std::cout << " " << testnum << " (" << testerr << ") The hash table contains " << cnt << " elements of the linear container: ";
		std::cout << ((tst = (cnt == num)) ? "Correct" : "Error") << "!" << std::endl;
	}
	catch (std::exception& exc)
	{
		std::cout << "\"" << exc.what() << "\": " << "Error!" << std::endl;
	}
	testerr += (1 - static_cast<unsigned int>(tst));
}

/* ************************************************************************** */

#endif
