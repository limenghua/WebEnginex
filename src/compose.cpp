#include "enginex/compose.h"

#include <ppltasks.h>
#include <enginex/middleware.h>
#include <enginex/context.h>
#include <vector>
#include <memory>

namespace enginex {

	namespace {
		task0 EmptyCall() {
			return task0([]() {});
		}


		class Composed :public std::enable_shared_from_this<Composed>
		{
		public:
			static std::shared_ptr<Composed> Create(const std::vector<Middleware> & middlewares)
			{
				return std::shared_ptr<Composed>(new Composed(middlewares));
			}

			task0 call(ContextPtr ctx, NextHandler next)
			{
				_index = -1;
				_ctx = ctx;
				_next = next;

				//return CreateNext(0)();
				return Dispatch(0);
			}

			NextHandler CreateNext(int i)
			{
				if (i <= _index)throw std::exception("next() called multiple times");
				_index = i;

				if (i == _middlewares.size()) {
					return _next?_next: EmptyCall;
				}

				if(i>_middlewares.size())return  EmptyCall;

				auto fn = _middlewares[i];
				auto next = CreateNext(i + 1);

				auto self = shared_from_this();
				return [fn, next,self]()->task0 {return fn(self->_ctx, next);};
			}

		private:
			Composed(const std::vector<Middleware> & middlewares) :
				_middlewares(middlewares),
				_index(-1),
				_ctx(nullptr),
				_next(nullptr)
			{}

			task0 Dispatch(int i)
			{
				if (i <= _index)throw std::exception("next() called multiple times");
				_index = i;

				if (i == _middlewares.size()) {
					if (_next) {
						return _next();
					}
					else {
						return EmptyCall();
					}
				}

				auto self = shared_from_this();
				NextHandler next = [self,i]() {return self->Dispatch(i + 1); };
				Middleware & fn = _middlewares[i];
				return fn(_ctx, next);
			}

			ContextPtr _ctx;
			std::vector<Middleware> _middlewares;
			NextHandler _next;
			int _index;
		};
	}

	Middleware Compose(const std::vector<Middleware> & middlewares)
	{
		return [middlewares](ContextPtr ctx, NextHandler next) {
			auto composed = Composed::Create(middlewares);
			return composed->call(ctx, next);
		};
	}

}
