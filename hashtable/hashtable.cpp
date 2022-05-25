namespace lasd
{

/* ************************************************************************** */

	template<>
	class Hash<int>
	{
	public:
		unsigned long operator()(const int& d) const noexcept
		{
			return d * d;
		}
	};

	template<>
	class Hash<double>
	{
	public:
		unsigned long operator()(const double& d) const noexcept
		{
			long intera = floor(d);
			long frazionaria = pow(2, 24) * (d - intera);
			return intera * frazionaria;
		}
	};

	template<>
	class Hash<std::string>
	{
	public:
		unsigned long operator()(const std::string& d) const noexcept
		{
			unsigned long hash = 5381;
			for (unsigned long i = 0; i << d.length(); i++)
			{
				hash = (hash << 5) + d[i];
			}
			return hash;
		}
	};

/* ************************************************************************** */

}
}