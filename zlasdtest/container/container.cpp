#include <iostream>

/* ************************************************************************** */

#include "../../container/container.hpp"

/* ************************************************************************** */

// Container member functions!

void Empty(unsigned int& testnum, unsigned int& testerr, const lasd::Container& con, bool chk)
{
	bool tst;
	testnum++;
	std::cout << " " << testnum << " (" << testerr << ") The container is " << ((tst = con.Empty()) ? "" : "not ") << "empty: ";
	std::cout << ((tst = (tst == chk)) ? "Correct" : "Error") << "!" << std::endl;
	testerr += (1 - static_cast<unsigned int>(tst));
}

void Size(unsigned int& testnum, unsigned int& testerr, const lasd::Container& con, bool chk, std::size_t siz)
{
	bool tst;
	testnum++;
	std::cout << " " << testnum << " (" << testerr << ") The container has size " << con.Size() << ": ";
	std::cout << ((tst = ((con.Size() == siz) == chk)) ? "Correct" : "Error") << "!" << std::endl;
	testerr += (1 - static_cast<unsigned int>(tst));
}

/* ************************************************************************** */

// Auxiliary functions for MappableContainer!

void MapStringAppend(std::string& dat, void *par)
{
	dat.append(*(static_cast<std::string *>(par)));
}

void MapStringNonEmptyAppend(std::string& dat, void *par)
{
	if (!dat.empty())
	{
		dat.append(*(static_cast<std::string *>(par)));
	}
}

/* ************************************************************************** */

// Auxiliary functions for FoldableContainer!

void FoldParity(const int& dat, const void *_, void *acc)
{
	*(static_cast<int *>(acc)) += dat;
	*(static_cast<int *>(acc)) %= 2;
}

void FoldStringConcatenate(const std::string& dat, const void *_, void *acc)
{
	(static_cast<std::string *>(acc))->append(dat);
}

/* ************************************************************************** */
