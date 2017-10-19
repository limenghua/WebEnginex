#pragma once
#include <memory>
#include <enginex/any-container.h>
#include<enginex/request.h>
#include<enginex/response.h>

namespace enginex {
	class Context: public AnyPtrContainer {
		Context(const Context &) = delete;
		Context & operator = (const Context &) = delete;
		Context(Context && ctx) = delete;
	public:
		Context(RequestPtr &req, ResponsePtr &res) {
			this->request = req;
			this->response = res;
		}

		using Pointer = std::shared_ptr<Context>;
		static Pointer Create(RequestPtr &req, ResponsePtr &res) {
			return std::make_shared<Context>(req, res);
		}
		
		RequestPtr request;
		ResponsePtr response;

	};
	using ContextPtr = Context::Pointer;
}