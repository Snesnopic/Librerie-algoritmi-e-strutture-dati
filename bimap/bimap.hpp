#ifndef BIMAP_HPP
#define BIMAP_HPP
#include <map>

namespace lasd
{
	template<typename KeyType, typename ValueType>
	class Bimap
	{
	protected:
		std::map<KeyType, ValueType> normalMap{};
		std::map<ValueType, KeyType> reverseMap{};

	public:
		void Set(const KeyType& key, const ValueType& value);
		void Set(KeyType&& key, ValueType&& value);

		const KeyType& KeyOfValue(const ValueType& value) const;
		const ValueType& ValueOfKey(const KeyType& key) const;

		bool RemoveKey(const KeyType& key);
		bool RemoveValue(const ValueType& value);

		bool HasKey(const KeyType& key) const;
		bool HasValue(const ValueType& value) const;

		[[nodiscard]] unsigned long Size() const;

		const std::map<ValueType, KeyType>& ValueMap() const;
		const std::unordered_map<KeyType, ValueType>& KeyMap() const;
		/*
		KeyType& operator[](const ValueType& value) const;
		ValueType& operator[](const KeyType& key) const;*/
	};
}
#include "bimap.cpp"
#endif