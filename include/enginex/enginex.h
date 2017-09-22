#pragma once
#include<memory>
#include<enginex/middleware.h>

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



	private:
		std::vector<Middleware> _middlewares;
	};
}
