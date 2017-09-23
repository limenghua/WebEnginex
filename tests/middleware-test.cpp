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
	Middleware handler = [](ContextPtr, NextHandler)->task0 {
		return task0();
	};

	CHECK_TRUE(!!handler);
}

TEST(MiddleWare, CallMiddlewareAsAFunction)
{
	Middleware handler = [&]( ContextPtr , NextHandler)->task0 {
		return create_task([]() {
			mock().actualCall("CallMiddlewareAsAFunction");
		});
	};
	
	mock().expectOneCall("CallMiddlewareAsAFunction");
	handler(nullptr, nullptr).wait();
	mock().checkExpectations();
}

TEST(MiddleWare, Copyable)
{
	Middleware handler;
	Middleware h = [&](ContextPtr, NextHandler)->task0 {
		return create_task([]() {
			mock().actualCall("Copyable"); 
		});
	};

	handler = h;
	mock().expectOneCall("Copyable");
	handler(nullptr, nullptr).wait();
	mock().checkExpectations();
}