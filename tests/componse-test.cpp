#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include <enginex/componse.h>
#include <enginex/middleware.h>
#include <vector>
#include <ppltasks.h>

using namespace enginex;
using namespace concurrency;


TEST_GROUP(MiddleComponse)
{
	void teardown()
	{
		mock().clear();
	}
};

TEST(MiddleComponse, ComponseEmptyContainer)
{
	std::vector<Middleware> middlewares;

	auto componseMiddleware = Componse(middlewares);

	CHECK_TRUE(!componseMiddleware);
}

TEST(MiddleComponse, ComponseOneMiddleware)
{
	//bool called = false;
	//Middleware mw = [&](Context &ctx, NextHandler &next)->task0 {
	//	called = true;
	//	return create_task([]() {});
	//};

	//std::vector<Middleware> middlewares;

	//middlewares.push_back(mw);

	//auto componseMiddleware = Componse(middlewares);

	//Context ctx;
	//componseMiddleware(ctx, nullptr).wait();


	//CHECK_TRUE(called);

}