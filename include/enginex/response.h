#pragma once
#include<enginex/message.h>
#include <enginex/any-container.h>

#include<memory>

namespace enginex {
	class Response :public Message, public AnyPtrContainer{
	public:
		using Pointer = std::shared_ptr<Response>;
		static Pointer Create() {
			return std::make_shared<Response>();
		}
	};

	using ResponsePtr = Response::Pointer;
}
