#include "enginex/message.h"

namespace enginex {
	static const std::string EMPTY_HEADER;

	std::string const & Message::GetHeader(std::string const & key)const
	{
		auto it = headers.find(key);
		if (it == headers.end())return EMPTY_HEADER;

		return it->second;
	}
	
	CiMap const & Message::GetHeaders()const
	{
		return headers;
	}

	Message::HeaderValues Message::GetHeaders(std::string const & key) const
	{
		HeaderValues values;
		auto range = headers.equal_range(key);
		for (auto it = range.first; it != range.second; it++) {
			values.push_back(it->second);
		}
		return values;
	}

	void Message::SetHeader(std::string const & key, std::string const & val)
	{
		headers.erase(key);
		return AppendHeader(key, val);
	}

	void Message::AppendHeader(std::string const & key, std::string const & val)
	{
		headers.emplace(key, val);
	}



}
