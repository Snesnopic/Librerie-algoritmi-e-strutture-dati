namespace lasd
{

/* ************************************************************************** */

	//Constructors
	//Initial size constructor
	template<typename Data>
	Vector<Data>::Vector(const unsigned long initialSize)
	{
		array = new Data[initialSize];
		size = initialSize;
	}
    template<typename Data>
    Vector<Data>::Vector(const unsigned long initialSize, const Data defaultValue) : Vector(initialSize)
    {
        for(auto i = 0; i<size;++i)
            array[i] = defaultValue;
    }

	//LinearContainer constructor
	template<typename Data>
	Vector<Data>::Vector(const LinearContainer<Data>& lc)
	{
		size = lc.Size();
		array = new Data[size];
		for (unsigned long i = 0; i < size; ++i)
			array[i] = lc[i];
	}

	//Copy constructor
	template<typename Data>
	Vector<Data>::Vector(const Vector<Data>& v)
	{
		size = v.size;
		array = new Data[v.size];
		std::copy(v.array, v.array + size, array);
	}

	//Move constructor
	template<typename Data>
	Vector<Data>::Vector(Vector<Data>&& v) noexcept
	{
		std::swap(array, v.array);
		std::swap(size, v.size);
	}

	//Destructor
	template<typename Data>
	Vector<Data>::~Vector()
	{
		delete[] array;
	}

	//Operators
	//Random access operator
	template<typename Data>
	Data& Vector<Data>::operator[](const unsigned long index) const
	{
		if (index >= size)
			throw std::out_of_range("Index out of bounds!");
		return array[index];
	}

	//Copy assignment
	template<typename Data>
	Vector<Data>& Vector<Data>::operator=(const Vector& v)
	{
		if (this != &v)
		{
			Data *tmp = new Data[v.size];
			std::copy(v.array, v.array + v.size, tmp);
			delete[]array;
			array = tmp;
			size = v.size;
		}
		return *this;
	}

	//Move assignment
	template<typename Data>
	Vector<Data>& Vector<Data>::operator=(Vector<Data>&& v) noexcept
	{
		if (this != &v)
		{
			std::swap(array, v.array);
			std::swap(size, v.size);
		}
		return *this;
	}

	//Equal comparison
	template<typename Data>
	bool Vector<Data>::operator==(const Vector& v) const noexcept
	{
		if (size != v.Size())
			return false;
		for (unsigned long i = 0; i < size; ++i)
		{
			if (array[i] != v[i])
				return false;
		}
		return true;
	}

	//Not equal comparison
	template<typename Data>
	bool Vector<Data>::operator!=(const Vector& v) const noexcept
	{
		return !(*this == v);
	}

	//Vector functions
	//Resize
	template<typename Data>
	void Vector<Data>::Resize(const unsigned long newSize)
	{
		if (newSize == 0)
			Clear();
		else
		{
			if (size != newSize)
			{
				Data *tmp = new Data[newSize];
				for (auto i = 0; i < std::min(size, newSize); ++i)
				{
					std::swap(array[i], tmp[i]);
				}
				delete[] array;
				array = tmp;
				size = newSize;
			}
		}
	}
#include <type_traits>
#include <utility>

    template<class T, class EqualTo>
    struct has_operator_equal_impl
    {
        template<class U, class V>
        static auto test(U*) -> decltype(std::declval<U>() < std::declval<V>());
        template<typename, typename>
        static auto test(...) -> std::false_type;

        using type = typename std::is_same<bool, decltype(test<T, EqualTo>(0))>::type;
    };

    template<class T, class EqualTo = T>
    struct has_operator_lessthan : has_operator_equal_impl<T, EqualTo>::type {};

    template<typename Data>
	void Vector<Data>::Sort() noexcept
	{
        if constexpr (has_operator_lessthan<Data>::value)
         std::sort(array, array + sizeof array / sizeof array[0]);
	}
    template<typename Data>
     Vector<Data>::operator std::vector<Data>() const
    {
         std::vector<Data> v(array, array + sizeof(array)/sizeof(array[0]));
         return v;
    }
    template<typename Data>
    void Vector<Data>::SortAscending() noexcept
    {
        Sort();
    }
    template<typename Data>
    void Vector<Data>::SortDescending() noexcept
    {
        if constexpr (has_operator_lessthan<Data>::value)
        std::sort(array + sizeof array / sizeof array[0],array,std::greater<>());
    }

	//Clear
	template<typename Data>
	void Vector<Data>::Clear()
	{
		size = 0;
		delete[] array;
		array = nullptr;
	}

	//Front
	template<typename Data>
	Data& Vector<Data>::Front() const
	{
		if (size == 0)
			throw std::length_error("Index out of bounds!");
		return array[0];
	}

	//Back
	template<typename Data>
	Data& Vector<Data>::Back() const
	{
		if (size == 0)
			throw std::length_error("Index out of bounds!");
		return array[size - 1];
	}

	//Map functions
	template<typename Data>
	void Vector<Data>::Map(MapFunctor f, void *par)
	{
		MapPreOrder(f, par);
	}

	template<typename Data>
	void Vector<Data>::MapPreOrder(MapFunctor f, void *par)
	{
		for (unsigned long i = 0; i < size; ++i)
		{
			f(array[i], par);
		}
	}

	template<typename Data>
	void Vector<Data>::MapPostOrder(MapFunctor f, void *par)
	{
		for (unsigned long i = 1; i <= size && size != 0; ++i)
		{
			f(array[size - i], par);
		}
	}

	//Fold functions
	template<typename Data>
	void Vector<Data>::Fold(FoldFunctor f, const void *par, void *acc) const
	{
		FoldPreOrder(f, par, acc);
	}

	template<typename Data>
	void Vector<Data>::FoldPreOrder(FoldFunctor f, const void *par, void *acc) const
	{
		for (unsigned long i = 0; i < size; ++i)
		{
			f(array[i], par, acc);
		}
	}

	template<typename Data>
	void Vector<Data>::FoldPostOrder(FoldFunctor f, const void *par, void *acc) const
	{
		for (unsigned long i = 1; i <= size && size != 0; ++i)
		{
			f(array[size - i], par, acc);
		}
	}
/* ************************************************************************** */

}
