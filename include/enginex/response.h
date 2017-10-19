#pragma once
#include<enginex/message.h>
#include <enginex/any-container.h>

#include<memory>

namespace enginex {
	class Response :public Message, public AnyPtrContainer{
	public:
		using Sender = std::function<void(const char *buffer, size_t lenth)>;
	public:
		using Pointer = std::shared_ptr<Response>;
		static Pointer Create() {
			return std::make_shared<Response>();
		}

		Sender SetSender(Sender fun) {
			auto tmp = sender;
			sender = fun;
			return tmp;
		}

	private:
		Sender sender;
	};

	using ResponsePtr = Response::Pointer;
}
