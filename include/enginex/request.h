#pragma once
#include<memory>
#include <enginex/message.h>
#include <enginex/any-container.h>

namespace enginex {
	class Request : public Message,public AnyPtrContainer {
	public:
		using Pointer = std::shared_ptr<Request>;
		static Pointer Create() {
			return std::make_shared<Request>();
		}

	};

	using RequestPtr = Request::Pointer;
}
