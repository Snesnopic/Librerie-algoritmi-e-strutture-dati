#pragma once
namespace lasd
{
/* ************************************************************************** */
//Container functions
	inline bool Container::Empty() const noexcept
	{
		return (size == 0);
	}

	inline unsigned long Container::Size() const noexcept
	{
		return size;
	}

//LinearContainer functions
	template<typename Data>
	bool LinearContainer<Data>::operator==(const LinearContainer& lc) const noexcept
	{
		if (size != lc.Size())
			return false;
		for (unsigned long i = 0; i < size; i++)
		{
			if (operator[](i) != lc[i])
				return false;
		}
		return true;
	}

	template<typename Data>
	bool LinearContainer<Data>::operator!=(const LinearContainer& lc) const noexcept
	{
		return !(*this == lc);
	}

	template<typename Data>
	Data& LinearContainer<Data>::Front() const
	{
		if (size == 0)
			throw std::length_error("Index out of bounds!");
		return operator[](0);
	}

	template<typename Data>
	Data& LinearContainer<Data>::Back() const
	{
		if (size == 0)
			throw std::length_error("Index out of bounds!");
		return operator[](size - 1);
	}

	template<typename Data>
	void DictionaryContainer<Data>::Insert(const LinearContainer<Data>& lc)// Copy of the value
	{
		for (unsigned long i = 0; i < lc.Size(); i++)
		{
			Insert(lc[i]);
		}
	}

	template<typename Data>
	void DictionaryContainer<Data>::Insert(LinearContainer<Data>&& lc) noexcept // Move of the value
	{
		for (unsigned long i = 0; i < lc.Size(); i++)
		{
			Insert(std::move(lc[i]));
		}
	}

	template<typename Data>
	void DictionaryContainer<Data>::Remove(const LinearContainer<Data>& lc) // Override DictionaryContainer member
	{
		for (unsigned long i = 0; i < lc.Size(); i++)
		{
			Remove(lc[i]);
		}
	}

//FoldableContainer functions
	template<typename Data>
	void AuxFoldExists(const Data& dat, const void *val, void *exists) noexcept
	{
		if (dat == *(static_cast<const Data *>(val)))
		{
			*(static_cast<bool *>(exists)) = true;
		}
	}

	template<typename Data>
	bool FoldableContainer<Data>::Exists(const Data& d) const noexcept
	{
		bool esiste = false;
		Fold(&AuxFoldExists<Data>, &d, &esiste);
		return esiste;
	}

//PreOrderMappableContainer functions
	template<typename Data>
	void PreOrderMappableContainer<Data>::Map(MapFunctor fun, void *par)
	{
		MapPreOrder(fun, par);
	}

//PreOrderFoldableContainer functions
	template<typename Data>
	void PreOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void *par, void *acc) const
	{
		FoldPreOrder(fun, par, acc);
	}

//PostOrderMappableContainer functions
	template<typename Data>
	void PostOrderMappableContainer<Data>::Map(MapFunctor fun, void *par)
	{
		MapPostOrder(fun, par);
	}

//PostOrderFoldableContainer functions
	template<typename Data>
	void PostOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void *par, void *acc) const
	{
		FoldPostOrder(fun, par, acc);
	}

//InOrderMappableContainer functions
	template<typename Data>
	void InOrderMappableContainer<Data>::Map(MapFunctor fun, void *par)
	{
		MapInOrder(fun, par);
	}

//InOrderFoldableContainer functions
	template<typename Data>
	void InOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void *par, void *acc) const
	{
		FoldInOrder(fun, par, acc);
	}

//BreadthMappableContainer functions
	template<typename Data>
	void BreadthMappableContainer<Data>::Map(MapFunctor fun, void *par)
	{
		MapBreadth(fun, par);
	}

//BreadthFoldableContainer functions
	template<typename Data>
	void BreadthFoldableContainer<Data>::Fold(FoldFunctor fun, const void *par, void *acc) const
	{
		FoldBreadth(fun, par, acc);
	}
/* ************************************************************************** */

}
