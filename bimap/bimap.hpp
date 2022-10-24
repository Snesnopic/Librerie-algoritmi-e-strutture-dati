#ifndef BIMAP_HPP
#define BIMAP_HPP

#include "container.hpp"
#include <map>

namespace lasd
{
	template<typename KeyType, typename ValueType>
	class Bimap
	{
	private:
		std::map<KeyType, ValueType> normalMap{};
		std::map<ValueType, KeyType> reverseMap{};

	public:
		void Set(const KeyType& key, const ValueType& value);

		KeyType& KeyOfValue(const ValueType& value);

		ValueType& ValueOfKey(const KeyType& key);

		bool RemoveKey(const KeyType& key);

		bool RemoveValue(const ValueType& value);

		bool HasKey(const KeyType& key) const;

		bool HasValue(const ValueType& value) const;

		[[nodiscard]] unsigned long Size() const;

		const std::map<ValueType, KeyType>& ValueMap() const;

		const std::unordered_map<KeyType, ValueType>& KeyMap() const;
	};
}
#endif