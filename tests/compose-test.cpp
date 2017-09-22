#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include <enginex/compose.h>
#include <enginex/middleware.h>
#include <vector>
#include <ppltasks.h>

#include "middlerware-gen.h"

using namespace enginex;
using namespace concurrency;


TEST_GROUP(MiddleCompose)
{
	void teardown()
	{
		mock().clear();
	}
};

TEST(MiddleCompose, ComponseEmptyContainer)
{
	std::vector<Middleware> middlewares;

	auto componseMiddleware = Compose(middlewares);

	CHECK_TRUE(componseMiddleware);
}

TEST(MiddleCompose, ComponseOneMiddleware)
{
	//bool called = false;
	Middleware mw = TestMiddleware("ComponseOneMiddleware");

	std::vector<Middleware> middlewares = { mw };

	auto componseMiddleware = Compose(middlewares);

	Context ctx;
	mock().expectOneCall("ComponseOneMiddleware");
	componseMiddleware(ctx, nullptr).wait();
	mock().checkExpectations();

}

TEST(MiddleCompose, ComponseTwoMiddleware)
{
	bool called = false;
	Middleware mw = TestMiddleware("ComponseTwoMiddleware");

	std::vector<Middleware> middlewares = { mw,mw };

	auto componseMiddleware = Compose(middlewares);

	Context ctx;
	mock().expectNCalls(2, "ComponseTwoMiddleware");
	componseMiddleware(ctx, nullptr).wait();
	mock().checkExpectations();
}

TEST(MiddleCompose, ComponseMoreMiddleware)
{
	bool called = false;
	Middleware mw = TestMiddleware("ComponseTwoMiddleware");
	Middleware mw2 = TestMiddleware("ComponseTwoMiddleware2");
	std::vector<Middleware> middlewares = { mw,mw2,mw,mw2,mw2 };

	auto componseMiddleware = Compose(middlewares);

	Context ctx;
	mock().expectNCalls(2, "ComponseTwoMiddleware");
	mock().expectNCalls(3, "ComponseTwoMiddleware2");
	componseMiddleware(ctx, nullptr).wait();
	mock().checkExpectations();
}

TEST(MiddleCompose, MiddlewareNotCallNext)
{
	int calledTimes = 0;
	Middleware callNextMw = [&](Context& ctx, NextHandler next) {
		calledTimes++;
		return next();
	};

	Middleware notCallNextMw = [&](Context& ctx, NextHandler next) {
		calledTimes++;
		return create_task([]() {});
	};

	std::vector<Middleware> middlewares = { callNextMw,notCallNextMw,callNextMw,callNextMw };

	auto componseMiddleware = Compose(middlewares);

	Context ctx;
	componseMiddleware(ctx, nullptr).wait();

	CHECK_EQUAL(calledTimes, 2);
}

TEST(MiddleCompose, InsideMiddlewareCall)
{
	int calledTimes = 0;
	Middleware callNextMw = [&](Context& ctx, NextHandler next) {
		calledTimes++;
		return next();
	};

	std::vector<Middleware> insideMiddlewares = { callNextMw,callNextMw,callNextMw };
	
	auto insideMw = Compose(insideMiddlewares);
	std::vector<Middleware> middlewares = { callNextMw,insideMw };
	auto newMiddlewares = Compose(middlewares);

	Context ctx;
	newMiddlewares(ctx, nullptr).wait();

	CHECK_EQUAL(calledTimes,4);
}