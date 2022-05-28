#include "bst.hpp"

namespace lasd
{

/* ************************************************************************** */

	// Specific constructors
	template<typename Data>
	BST<Data>::BST(const LinearContainer<Data>& lc) // A bst obtained from a LinearContainer
	{
		Insert(lc);
	}

	// Copy assignment
	template<typename Data>
	BST<Data>& BST<Data>::operator=(const BST& bst)
	{
		BinaryTreeLnk<Data>::operator=(bst);
		return *this;
	}

	// Move assignment
	template<typename Data>
	BST<Data>& BST<Data>::operator=(BST&& bst) noexcept
	{
		BinaryTreeLnk<Data>::operator=(std::move(bst));
		return *this;
	}

	// Comparison operators
	template<typename Data>
	bool BST<Data>::operator==(const BST& bst) const noexcept
	{
		if (size == bst.size)
		{
			BTInOrderIterator<Data> i(*this);
			BTInOrderIterator<Data> j(bst);
			while (!i.Terminated())
			{
				if (*i != *j)
					return false;
				++i;
				++j;
			}
			return true;
		}
		else
			return false;
	}

	template<typename Data>
	bool BST<Data>::operator!=(const BST& bst) const noexcept
	{
		return !(*this == bst);
	}

	template<typename Data>
	bool BST<Data>::Insert(const Data& d) // Override DictionaryContainer member (Copy of the value)
	{
		NodeLnk *& ptr = FindPointerTo(root, d);
		if (ptr == nullptr)
	{
		size++;
		ptr = new NodeLnk(d);
		return true;
	}
	return false;
	}

	template<typename Data>
	bool BST<Data>::Insert(Data&& d) noexcept // Override DictionaryContainer member (Move of the value)
	{
	NodeLnk *& ptr = FindPointerTo(root, d);
	if (ptr == nullptr)
	{
	size++;
	ptr = new NodeLnk(std::move(d));
	return true;
	}
	return false;
	}

	template<typename Data>
	bool BST<Data>::Remove(const Data& d) // Override DictionaryContainer member
	{
		NodeLnk *& ptr = FindPointerTo(root, d);
		if (ptr != nullptr)
		{
		delete Detach(ptr);
		return true;
		}
		return false;
	}
/* ************************************************************************** */

}
