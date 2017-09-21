#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include <ppltasks.h>
#include <enginex/middleware.h>
#include <vector>

using namespace enginex;
using namespace concurrency;

typedef task<void> task0;

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
	Context txt;
	Middleware handler = [&](Context& ctx, Middleware &next)->task0 {
		return create_task([&]() {
			mock().actualCall("ConstructWithLambda");
		});
	};

	mock().expectOneCall("ConstructWithLambda");
	auto task = handler(txt, handler);
	task.wait();
	mock().checkExpectations();
}

TEST(MiddleWare, ConvertToTaskFuction)
{
	Context txt;
	auto handler = [&](Context& ctx, Middleware &next)->void {
		mock().actualCall("ConvertToTaskFuction");
	};
	Middleware middle = Middleware::Convert(handler);
	
	mock().expectOneCall("ConvertToTaskFuction");
	auto task = middle(txt, middle);
	task.wait();
	mock().checkExpectations();
}

TEST(MiddleWare, Copyable)
{
	Context txt;
	auto handler = [&](Context& ctx, Middleware &next)->void {
		mock().actualCall("ConvertToTaskFuction");
	};
	Middleware middle = Middleware::Convert(handler);

	std::vector<Middleware> middles = { middle,middle };

	mock().expectNCalls(2, "ConvertToTaskFuction");

	for (auto & mid : middles) {
		mid(txt, mid).wait();
	}
	
	mock().checkExpectations();
}