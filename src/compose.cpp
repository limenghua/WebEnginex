#pragma once
#include<enginex/compose.h>
#include <ppltasks.h>
#include <enginex/middleware.h>
#include <enginex/context.h>
#include <vector>
#include <memory>

namespace enginex {

	namespace {
		task0 EmptyTask0() {
			return concurrency::create_task([]() {});
		}

		class Composed :public std::enable_shared_from_this<Composed>
		{
		public:
			static std::shared_ptr<Composed> Create(const std::vector<Middleware> & middlewares)
			{
				return std::shared_ptr<Composed>(new Composed(middlewares));
			}

			task0 call(Context & ctx, NextHandler next)
			{
				_index = -1;
				return Dispatch(0, ctx, next);
			}

		private:
			Composed(const std::vector<Middleware> & middlewares) :
				_middlewares(middlewares),
				_index(-1)
			{}

			task0 Dispatch(int i, Context & ctx, NextHandler next)
			{
				if (i <= _index)throw std::exception("next() called multiple times");
				_index = i;

				if (i == _middlewares.size()) {
					if (next) {
						return next();
					}
					else {
						return EmptyTask0();
					}
				}
				NextHandler n = [i, this, &ctx, next]() {return Dispatch(i + 1, ctx, next); };
				Middleware & fn = _middlewares[i];
				return fn(ctx, n);
			}

			std::vector<Middleware> _middlewares;
			int _index;
		};
	}

	Middleware Compose(const std::vector<Middleware> & middlewares)
	{
		auto composed = Composed::Create(middlewares);

		return [composed](Context& ctx, NextHandler next) {
			return composed->call(ctx, next);
		};
	}

}
