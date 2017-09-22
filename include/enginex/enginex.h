#pragma once
#include<memory>

namespace enginex {
	class WebEnginex
	{
	public:
		using Pointer = std::shared_ptr<WebEnginex>;
		static Pointer Create() {
			return std::make_shared<WebEnginex>();
		}
	};
}
