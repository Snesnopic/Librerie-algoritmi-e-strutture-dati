namespace lasd
{

/* ************************************************************************** */

// Specific member functions (inherited from Container)
	template<typename Data>
	BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& lc) // A binary tree obtained from a LinearContainer
	{
		size = lc.Size();
		array.Resize(size);
		for (std::size_t i = 0; i < array.Size(); ++i)
		{
			array[i] = new NodeVec(&array, i, lc[i]);
		}
	}

	/* ************************************************************************ */

	// Copy constructor
	template<typename Data>
	BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec& btv)
	{
		size = btv.size;
		array.Resize(btv.array.Size());
		for (std::size_t i = 0; i < array.Size(); ++i)
		{
			array[i] = new NodeVec(&array, i, btv.array[i]->dato);
		}
	}

	// Move constructor
	template<typename Data>
	BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec&& btv) noexcept
	{
		std::swap(size, btv.size);
		std::swap(array, btv.array);
		for (std::size_t i = 0; i < array.Size(); ++i)
		{
			array[i]->arrayRef = &array;
		}
	}
	/* ************************************************************************ */

	// Destructor
	template<typename Data>
	BinaryTreeVec<Data>::~BinaryTreeVec()
	{
		for (std::size_t i = 0; i < array.Size(); ++i)
		{
			if (array[i] != nullptr)
				delete array[i];
		}
	}

	template<typename Data>
	void BinaryTreeVec<Data>::Clear() // Override Container member
	{
		for (std::size_t i = 0; i < array.Size(); ++i)
		{
			if (array[i] != nullptr)
				delete array[i];
		}
		size = 0;
		array.Clear();
	}

	// Copy assignment
	template<typename Data>
	BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec& btv)
	{
		if (this != &btv)
		{
			array.Resize(btv.size);
			size = btv.size;
			for (std::size_t i = 0; i < size; ++i)
			{
				array[i] = new NodeVec(&array, i, btv.array[i]->dato);
			}
		}
		return *this;
	}

	// Move assignment
	template<typename Data>
	BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec&& btv) noexcept
	{
		if (this != &btv)
		{
			std::swap(array, btv.array);
			std::swap(size, btv.size);
		}
		return *this;
	}

	// Specific member functions (inherited from BreadthMappableContainer)
	template<typename Data>
	void BinaryTreeVec<Data>::MapBreadth(MapFunctor f, void *par) // Override BreadthMappableContainer member // Override BreadthMappableContainer member
	{
		for (std::size_t i = 0; i < array.Size(); ++i)
		{
			if (array[i] != nullptr)
				f(array[i]->dato, par);
		}
	}

	/* ************************************************************************ */

	// Specific member functions (inherited from BreadthFoldableContainer)
	template<typename Data>
	void BinaryTreeVec<Data>::FoldBreadth(FoldFunctor f, const void *par, void *acc) const // Override BreadthFoldableContainer member
	{
		for (std::size_t i = 0; i < array.Size(); ++i)
		{
			if (array[i] != nullptr)
				f(array[i]->dato, par, acc);
		}
	}

/* ************************************************************************** */

}
