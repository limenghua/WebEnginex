#include "enginex/message.h"

namespace enginex {
	static const std::string EMPTY_HEADER;

	std::string const & Message::GetHeader(std::string const & key)const
	{
		auto it = _headers.find(key);
		if (it == _headers.end())return EMPTY_HEADER;

		if (it->second.empty())return EMPTY_HEADER;
		return it->second.back();
	}
	
	Message::HeaderList const & Message::GetHeaders()const
	{
		return _headers;
	}

	void Message::AppendHeader(std::string const & key, std::string const & val)
	{
		_headers[key].push_back(val);
	}



}
