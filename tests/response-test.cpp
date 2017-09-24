#include <CppUTest/TestHarness.h>
#include <enginex/response.h>

using enginex::Response;
using enginex::ResponsePtr;


TEST_GROUP(Response)
{

};

TEST(Response, Construct)
{
	ResponsePtr res = Response::Create();

	//CHECK_TRUE(false);
}
