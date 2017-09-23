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

		task0 Handle(ContextPtr ctx) {
			auto fn = Compose(_middlewares);
			auto self = shared_from_this();

			return fn(ctx, nullptr).then([ctx, fn, self] {
				return self->Response(ctx);
			});
		}

		virtual void Response(ContextPtr ctx) {
			
		}




	private:
		std::vector<Middleware> _middlewares;
	};
}
