#include "bimap.hpp"

namespace lasd
{

	template <typename KeyType, typename ValueType>
	void Bimap<KeyType,ValueType>::Set(const KeyType& key, const ValueType& value)
	{
		normalMap.insert(key, value);
		reverseMap[value].insert(key);
	}

	template <typename KeyType, typename ValueType>
	KeyType& Bimap<KeyType,ValueType>::KeyOfValue(const ValueType &value)
	{
		return reverseMap.at(value);
	}

	template <typename KeyType, typename ValueType>
	ValueType& Bimap<KeyType,ValueType>::ValueOfKey(const KeyType &key)
	{
		return normalMap.at(key);
	}

	template <typename KeyType, typename ValueType>
	bool Bimap<KeyType,ValueType>::RemoveKey(const KeyType& key)
	{

		auto exists = HasValue(key);
		if (exists)
		{
			auto &value = valueForKey(key);
			auto &keys = keysForValue(value);
			keys.erase(key);
			if (keys.empty())
				reverseMap.erase(value);

			normalMap.erase(key);
		}
		return exists;
	}

	template <typename KeyType, typename ValueType>
	bool Bimap<KeyType,ValueType>::RemoveValue(const ValueType& value)
	{
		auto exists = HasValue(value);
		if (exists)
		{
			auto &keys = keysForValue(value);
			for (auto item : keys)
				normalMap.erase(item);
			reverseMap.erase(value);
		}
		return exists;
	}

	template <typename KeyType, typename ValueType>
	bool Bimap<KeyType,ValueType>::HasKey(const KeyType& key) const
	{
		return normalMap.contains(key);
	}

	template <typename KeyType, typename ValueType>
	bool Bimap<KeyType,ValueType>::HasValue(const ValueType& value) const
	{
		return reverseMap.contains(value);
	}

	template <typename KeyType, typename ValueType>
	[[nodiscard]] unsigned long Bimap<KeyType,ValueType>::Size() const
	{
		return normalMap.size();
	}

	template <typename KeyType, typename ValueType>
	const std::map<ValueType, KeyType>& Bimap<KeyType,ValueType>::ValueMap() const
	{
		return reverseMap;
	};

	template <typename KeyType, typename ValueType>
	const std::unordered_map<KeyType, ValueType>& Bimap<KeyType,ValueType>::KeyMap() const
	{
		return normalMap;
	};
}