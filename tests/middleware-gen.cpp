#include <CppUTestExt/MockSupport.h>
#include "middlerware-gen.h"
#include<enginex/context.h>
#include <ppltasks.h>

using namespace enginex;
using namespace concurrency;

enginex::Middleware TestMiddleware(std::string callName)
{
	return [callName](ContextPtr, NextHandler next)->task0 {
		mock().actualCall(callName.c_str());
		if (next) {
			return next();
		}
		return create_task([=](){});
	};
}

enginex::Middleware SimpleMiddleware()
{
	return [](ContextPtr, NextHandler next) {
		return create_task([]() {});
	};
}