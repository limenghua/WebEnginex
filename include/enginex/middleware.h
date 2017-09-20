#pragma once
#include <ppltasks.h>
#include <enginex/context.h>

namespace enginex {
	class Middleware
	{
	public:
		typedef concurrency::task<void> task0;
		typedef std::function< task0(Context &, Middleware &)>  Handler;

		Middleware(const Handler & h) :_handler(h)
		{}

		Middleware() :_handler()
		{}

		Middleware(const Middleware & other) :
			_handler(other._handler)
		{}

		Middleware(Middleware && other) :
			_handler(other._handler)
		{}

		Middleware & operator=(const Middleware & m) {
			_handler = m._handler;
		}

		Middleware & operator=(const Handler & h) {
			_handler = h;
		}

		task0 operator()(Context& ctx, Middleware & next)
		{
			_ASSERT(!!_handler);
			return _handler(ctx, next);
		}

		explicit operator bool() const
		{
			return !!_handler;
		}

	private:
		Handler _handler;
	};
}
