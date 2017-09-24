#include<CppUTest/TestHarness.h>
#include <enginex/request.h>

using namespace enginex;

TEST_GROUP(Request)
{

};

TEST(Request, construct)
{
	RequestPtr req = Request::Create();
}