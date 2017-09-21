#pragma once

#include <enginex/middleware.h>
#include <enginex/context.h>
#include <vector>

namespace enginex {


inline Middleware Componse(const std::vector<Middleware> & middlewares)
{
	if(middlewares.empty())return Middleware();

	return middlewares[0];
	//Middleware res = [middlewares](Context & ctx, Middleware & mdw)->task0 {


	//};
}


}
