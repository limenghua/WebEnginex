#include <CppUTest/TestHarness.h>
#include <ppltasks.h>
#include <enginex/context.h>
#include <functional>
#include <vector>

#include<enginex/middleware.h>

using namespace enginex;
using namespace concurrency;

typedef task<void> task0;

TEST_GROUP(MiddleWare)
{

};

TEST(MiddleWare, Construct)
{
	Middleware handler;

	CHECK_TRUE(!handler);
}

TEST(MiddleWare, ConstructWithLambda)
{
	Context txt;
	bool called = false;
	Middleware handler = [&](Context& ctx, Middleware &next)->task0 {
		return create_task([&]() {
			called = true;
		});
	};

	auto task = handler(txt, handler);
	task.wait();
	CHECK_TRUE(called);
}

TEST(MiddleWare, ConvertToTaskFuction)
{
	Context txt;
	bool called = false;
	auto handler = [&](Context& ctx, Middleware &next)->void {
		called = true;
	};
	Middleware middle = Middleware::Convert(handler);
	

	auto task = middle(txt, middle);
	task.wait();
	CHECK_TRUE(called);
}