#pragma once
#include<memory>

namespace enginex {
	class Request {
	public:
		using Pointer = std::shared_ptr<Request>;

	};

	using RequestPtr = Request::Pointer;	
}
