#include<CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include<enginex/enginex.h>
#include "middlerware-gen.h"

using namespace enginex;

TEST_GROUP(WebEnginex)
{

};

TEST(WebEnginex, Constructor)
{
	WebEnginex::Pointer app = WebEnginex::Create();
}

TEST(WebEnginex, UseAMiddleware)
{
	WebEnginex::Pointer app = WebEnginex::Create();
	auto middleware1 = TestMiddleware("UseAMiddleware1");
	auto middleware2 = TestMiddleware("UseAMiddleware2");

	app->Use(middleware1);
	app->Use(middleware2);

	mock().expectNCalls(1, "UseAMiddleware1");
	mock().expectNCalls(1, "UseAMiddleware2");

	app->Handle(nullptr).wait();
	mock().checkExpectations();
}