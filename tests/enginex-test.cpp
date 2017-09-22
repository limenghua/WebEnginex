#include<CppUTest/TestHarness.h>
#include<enginex/enginex.h>

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

}