#pragma once
#include<memory>
#include<enginex/middleware.h>
#include <enginex/compose.h>
#include <ppltasks.h>

namespace enginex {
	class WebEnginex:public std::enable_shared_from_this<WebEnginex>
	{
	public:
		using Pointer = std::shared_ptr<WebEnginex>;
		static Pointer Create() {
			return std::make_shared<WebEnginex>();
		}

	public:
		Pointer Use(Middleware & m) {
			_middlewares.push_back(m);
			return shared_from_this();
		}

		task0 Handle(Context & ctx) {
			auto ctxPtr = ContextPtr(new Context(std::move(ctx)));
			auto fn = Compose(_middlewares);
			auto self = shared_from_this();

			return fn(*ctxPtr, nullptr).then([ctxPtr, fn, self] {
				return self->Response(ctxPtr);
			});
		}

		void Response(ContextPtr ctx) {
			
		}




	private:
		std::vector<Middleware> _middlewares;
	};
}
