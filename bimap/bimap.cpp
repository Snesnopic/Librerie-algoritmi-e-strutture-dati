#include "bimap.hpp"

namespace lasd
{

	template <typename KeyType, typename ValueType>
	void Bimap<KeyType,ValueType>::Set(const KeyType& key, const ValueType& value)
	{
		normalMap.emplace(key, value);
		reverseMap.emplace(value, key);
	}

	template <typename KeyType, typename ValueType>
	void Bimap<KeyType,ValueType>::Set(KeyType&& key, ValueType&& value)
	{
        auto keyTemp = std::move(key);
        auto valueTemp = std::move(value);
		normalMap.emplace(keyTemp, valueTemp);
		reverseMap.emplace(valueTemp, keyTemp);
	}
	template <typename KeyType, typename ValueType>
	const KeyType& Bimap<KeyType,ValueType>::KeyOfValue(const ValueType& value) const
	{
		return reverseMap.at(value);
	}

	template <typename KeyType, typename ValueType>
	const ValueType& Bimap<KeyType,ValueType>::ValueOfKey(const KeyType& key) const
	{
		return normalMap.at(key);
	}

	template <typename KeyType, typename ValueType>
	bool Bimap<KeyType,ValueType>::RemoveKey(const KeyType& key)
	{
		auto exists = normalMap.contains(key);
		if (exists)
		{
			normalMap.erase(key);
			reverseMap.erase(ValueOfKey(key));
		}
		return exists;
	}

	template <typename KeyType, typename ValueType>
	bool Bimap<KeyType,ValueType>::RemoveValue(const ValueType& value)
	{
		auto exists = reverseMap.contains(value);
		if (exists)
		{
			normalMap.erase(KeyOfValue(value));
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
	const std::unordered_map<ValueType, KeyType>& Bimap<KeyType,ValueType>::ValueMap() const
	{
		return reverseMap;
	};

	template <typename KeyType, typename ValueType>
	const std::unordered_map<KeyType, ValueType>& Bimap<KeyType,ValueType>::KeyMap() const
	{
		return normalMap;
	};

	template <typename KeyType, typename ValueType>
	KeyType& Bimap<KeyType,ValueType>::operator[](const ValueType& value) const
	{
		return reverseMap[value];
	}

	template <typename KeyType, typename ValueType>
	ValueType& Bimap<KeyType,ValueType>::operator[](const KeyType& key) const
	{
		return normalMap[key];
	}
}