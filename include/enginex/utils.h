#pragma once

#include <unordered_map>
#include <functional>
#include <algorithm>

namespace enginex {
	inline std::string ToUpper(const std::string & str)
	{
		std::string newKey = str;
		std::transform(newKey.begin(), newKey.end(), newKey.begin(), toupper);
		return newKey;
	}

	struct CiHash
	{
		size_t operator()(const std::string& key) const
		{
			std::string newKey = ToUpper(key);
			return std::hash<std::string>()(newKey);
		}
	};

	struct CiEqual
	{
		bool operator()(const std::string& l, const std::string& r) const
		{
			return ToUpper(l) == ToUpper(r);
		}
	};

	using CiMap = std::unordered_multimap<std::string, std::string, CiHash, CiEqual>;
}
