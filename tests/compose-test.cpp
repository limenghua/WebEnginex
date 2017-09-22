#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include <enginex/compose.h>
#include <enginex/middleware.h>
#include <vector>
#include <ppltasks.h>

using namespace enginex;
using namespace concurrency;

Middleware TestMiddleware(std::string callName)
{
	return [callName](Context &, NextHandler next)->task0 {
		return create_task([=]() {
			mock().actualCall(callName.c_str());
			if (next) {
				return next();
			}
		});
	};
}


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