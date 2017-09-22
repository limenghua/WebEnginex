#include<CppUTest/TestHarness.h>
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
	auto middleware = SimpleMiddleware();

	app->Use(middleware);
}