#pragma once
#include <ppltasks.h>
#include <enginex/context.h>

namespace enginex {
	using task0 = concurrency::task<void>;
	using NextHandler = std::function<task0()>;
	using Middleware = std::function < task0(Context&, NextHandler)> ;
}
