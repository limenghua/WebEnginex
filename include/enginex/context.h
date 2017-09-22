#pragma once
#include <memory>


namespace enginex {
	class Context {
		Context(const Context &) = delete;
		Context & operator = (const Context &) = delete;
	public:
		Context(){}
		Context(Context && ctx){}
		

	};
	typedef std::shared_ptr<Context> ContextPtr;

}