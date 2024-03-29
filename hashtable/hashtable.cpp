namespace lasd
{

/* ************************************************************************** */

	template<>
	class Hash<int>
	{
	public:
		std::size_t operator()(const int& d) const noexcept
		{
			return static_cast<size_t>(d) * static_cast<size_t>(d);
		}
	};

	template<>
	class Hash<long>
	{
	public:
		std::size_t operator()(const long& d) const noexcept
		{
			return static_cast<size_t>(d) * static_cast<size_t>(d);
		}
	};

	template<>
	class Hash<double>
	{
	public:
		std::size_t operator()(const double& d) const noexcept
		{
			return reinterpret_cast<const std::size_t&>(d);
		}
	};

	template<>
	class Hash<float>
	{
	public:
		std::size_t operator()(const float& d) const noexcept
		{
			return reinterpret_cast<const std::size_t&>(d);
		}
	};

	template<>
	class Hash<std::string>
	{
	public:
		std::size_t operator()(const std::string& d) const noexcept
		{
			std::size_t hash = 5381;
			for (std::size_t i = 0; i < d.length(); ++i)
			{
				hash = (hash << 5) + d[i];
			}
			return hash;
		}
	};

	// Generic hash function (for other basic types, unions, structs and some STL classes)
	template<typename Data>
	std::size_t Hash<Data>::operator()(const Data& d) const noexcept
	{
		void *v = static_cast<void *>(&d);
		size_t j = sizeof(d);
		std::string s = "";
		for (size_t k = 0; k < j; k++)
		{
			s.push_back((static_cast<char *>(v))[k]);
		}
		return Hash<std::string>{}(s);
	}

	//Constructor
	template<typename Data>
	HashTable<Data>::HashTable()
	{
		std::default_random_engine gen(std::random_device{}());
		std::uniform_int_distribution<std::size_t> dista(5, 5381);
		while (true)
		{
			a = dista(gen);
			if (a <= 1)
				continue;
			if (a <= 3)
				break;
			if (a % 2 == 0 || a % 3 == 0)
				continue;
			for (std::size_t i = 5; i <= sqrt(a); i += 2)
			{
				if (a % i == 0 || a % (i + 2) == 0)
					continue;
			}
			break;
		}
		std::uniform_int_distribution<std::size_t> distb(2, a - 1);
		while (true)
		{
			b = distb(gen);
			if (b <= 3)
				break;
			if (b % 2 == 0 || b % 3 == 0)
				continue;
			for (std::size_t i = 5; i <= sqrt(b); i += 2)
			{
				if (b % i == 0 || b % (i + 2) == 0)
					continue;
			}
			break;
		}
	}

	// Copy assignment
	template<typename Data>
	HashTable<Data>& HashTable<Data>::operator=(const HashTable& ht) // Copy assignment of abstract types should not be possible.
	{
		a = ht.a;
		b = ht.b;
		return *this;
	}

	// Move assignment
	template<typename Data>
	HashTable<Data>& HashTable<Data>::operator=(HashTable&& ht) noexcept // Move assignment of abstract types should not be possible.
	{
		size = std::move(ht.size);
		a = std::move(ht.a);
		b = std::move(ht.b);
		return *this;
	}
/* ************************************************************************** */

}
