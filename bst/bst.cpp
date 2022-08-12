#include "bst.hpp"

namespace lasd
{

/* ************************************************************************** */


	// Default constructor
	template<typename Data>
	BST<Data>::BST()
	{
		size = 0;
		root = nullptr;
	}

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

	// Specific member functions
	template<typename Data>
	const Data& BST<Data>::Min() const // (concrete function must throw std::length_error when empty)
	{
		if (size == 0)
			throw std::length_error("Length error!");
		return FindPointerToMin(root)->dato;
	}

	template<typename Data>
	Data BST<Data>::MinNRemove() // (concrete function must throw std::length_error when empty)
	{
		if (size == 0)
			throw std::length_error("Length error!");
		NodeLnk *ptr = DetachMin(root);
		return DataNDelete(ptr);
	}

	template<typename Data>
	void BST<Data>::RemoveMin() // (concrete function must throw std::length_error when empty)
	{

		if (size == 0)
			throw std::length_error("Length error!");
		NodeLnk *ptr = DetachMin(root);
		delete ptr;
	}

	template<typename Data>
	const Data& BST<Data>::Max() const // (concrete function must throw std::length_error when empty)
	{
		if (size == 0)
			throw std::length_error("Length error!");
		return FindPointerToMax(root)->dato;
	}

	template<typename Data>
	Data BST<Data>::MaxNRemove() // (concrete function must throw std::length_error when empty)
	{
		if (size == 0)
			throw std::length_error("Length error!");
		NodeLnk *ptr = DetachMax(root);
		return DataNDelete(ptr);
	}

	template<typename Data>
	void BST<Data>::RemoveMax() // (concrete function must throw std::length_error when empty)
	{
		if (size == 0)
			throw std::length_error("Length error!");
		NodeLnk *ptr = DetachMax(root);
		delete ptr;
	}

	template<typename Data>
	const Data& BST<Data>::Predecessor(const Data& d) const // (concrete function must throw std::length_error when not found)
	{
		NodeLnk *const *ptr = FindPointerToPredecessor(root, d);
		if (ptr == nullptr)
			throw std::length_error("Length error!");
		return (*ptr)->dato;
	}

	template<typename Data>
	Data BST<Data>::PredecessorNRemove(const Data& d) // (concrete function must throw std::length_error when not found)
	{
		NodeLnk **ptr = FindPointerToPredecessor(root, d);
		if (ptr == nullptr)
			throw std::length_error("Length error!");
		Data& nd((*ptr)->dato);
		Remove((*ptr)->dato);
		return nd;
	}

	template<typename Data>
	void BST<Data>::RemovePredecessor(const Data& d) // (concrete function must throw std::length_error when not found)
	{
		NodeLnk **ptr = FindPointerToPredecessor(root, d);
		if (ptr == nullptr)
			throw std::length_error("Length error!");
		Remove((*ptr)->dato);
	}

	template<typename Data>
	const Data& BST<Data>::Successor(const Data& d) const // (concrete function must throw std::length_error when not found)
	{
		NodeLnk *const *ptr = FindPointerToSuccessor(root, d);
		if (ptr == nullptr)
			throw std::length_error("Length error!");
		return (*ptr)->dato;
	}

	template<typename Data>
	Data BST<Data>::SuccessorNRemove(const Data& d) // (concrete function must throw std::length_error when not found)
	{
		NodeLnk **ptr = FindPointerToSuccessor(root, d);
		if (ptr == nullptr)
			throw std::length_error("Length error!");
		Data& nd((*ptr)->dato);
		Remove((*ptr)->dato);
		return nd;
	}

	template<typename Data>
	void BST<Data>::RemoveSuccessor(const Data& d) // (concrete function must throw std::length_error when not found)
	{
		NodeLnk **ptr = FindPointerToSuccessor(root, d);
		if (ptr == nullptr)
			throw std::length_error("Length error!");
		Remove((*ptr)->dato);
	}

	// Specific member functions (inherited from DictionaryContainer)
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

	// Specific member functions (inherited from TestableContainer)
	template<typename Data>
	bool BST<Data>::Exists(const Data& d) const noexcept // Override TestableContainer member
	{
		if (size == 0)
			return false;
		return FindPointerTo(root, d) != nullptr;
	}

	// Auxiliary member functions
	template<typename Data>
	Data BST<Data>::DataNDelete(NodeLnk *n)
	{
		Data d = n->dato;
		delete n;
		return d;
	}
}