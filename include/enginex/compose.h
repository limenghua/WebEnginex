#pragma once
#include <enginex/middleware.h>
#include <vector>


namespace enginex {

Middleware Compose(const std::vector<Middleware> & middlewares);

}
