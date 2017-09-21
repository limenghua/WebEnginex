#pragma once
#include <ppltasks.h>
#include <enginex/context.h>

namespace enginex {
	
	class Middleware
	{
	public:
		typedef concurrency::task<void> task0;
		typedef std::function< task0(Context &, Middleware &)>  RequestHandler;
		typedef std::function< void(Context &, Middleware &)>  Handler;

		Middleware(const RequestHandler & h) :_handler(h)
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

		Middleware & operator=(const RequestHandler & h) {
			_handler = h;
		}

		task0 operator()(Context& ctx, Middleware & next){
			_ASSERT(!!_handler);
			return _handler(ctx, next);
		}

		explicit operator bool() const{
			return !!_handler;
		}

		RequestHandler Callback() {
			return _handler;
		}

		static RequestHandler Convert(Handler h) {
			return [h](Context & ctx, Middleware & next)->task0 {
				return concurrency::create_task([&] {
					return h(ctx, next);
				});
			};
		}

	private:
		RequestHandler _handler;
	};

}
