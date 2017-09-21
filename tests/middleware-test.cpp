#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include <ppltasks.h>
#include <enginex/middleware.h>
#include <vector>

using namespace enginex;
using namespace concurrency;

TEST_GROUP(MiddleWare)
{
	void teardown()
	{
		mock().clear();
	}
};

TEST(MiddleWare, Construct)
{
	Middleware handler;

	CHECK_TRUE(!handler);
}

TEST(MiddleWare, ConstructWithLambda)
{
	Middleware handler = [](Context& ctx, NextHandler next)->task0 {
		return task0();
	};

	CHECK_TRUE(!!handler);
}

TEST(MiddleWare, CallMiddlewareAsAFunction)
{
	Context txt;
	int callTimes = 0;
	Middleware handler = [&](Context& ctx, NextHandler next)->task0 {
		callTimes++;
		return create_task([]() {});
	};
	
	handler(txt, nullptr).wait();
	CHECK_EQUAL(callTimes, 1);
}

TEST(MiddleWare, Copyable)
{
	Context txt;
	int callTimes = 0;
	auto handler = [&](Context& ctx, NextHandler next)->task0 {
		callTimes++;
		return create_task([]() {});
	};

	std::vector<Middleware> middles = { handler,handler };
	for (auto & mid : middles) {
		//mid(txt, nullptr).get();
	}

	CHECK_EQUAL(callTimes, 2);
}