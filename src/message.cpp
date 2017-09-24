#include "enginex/message.h"

namespace enginex {
	static const std::string EMPTY_HEADER;

	std::string const & Message::GetHeader(std::string const & key)const
	{
		auto it = _headers.find(key);
		if (it == _headers.end())return EMPTY_HEADER;

		return it->second;
	}
	
	CiMap const & Message::GetHeaders()const
	{
		return _headers;
	}

	Message::HeaderValues Message::GetHeaders(std::string const & key) const
	{
		HeaderValues values;
		auto range = _headers.equal_range(key);
		for (auto it = range.first; it != range.second; it++) {
			values.push_back(it->second);
		}
		return values;
	}

	void Message::SetHeader(std::string const & key, std::string const & val)
	{
		_headers.erase(key);
		return AppendHeader(key, val);
	}

	void Message::AppendHeader(std::string const & key, std::string const & val)
	{
		_headers.emplace(key, val);
	}



}
