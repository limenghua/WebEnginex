#include<CppUTest/TestHarness.h>

#include<enginex/context.h>
#include<enginex/request.h>
#include<enginex/response.h>

using namespace enginex;

TEST_GROUP(Context)
{

};

TEST(Context, ShoudHasRequestMember)
{
	auto req = Request::Create();
	auto res = Response::Create();
	auto ctx = Context::Create(req, res);

	CHECK_TRUE(ctx->request == req);
	CHECK_TRUE(ctx->response == res);
}

TEST(Context, ShoudInheritFromAnyPtrContainer)
{
	auto req = Request::Create();
	auto res = Response::Create();
	auto ctx = Context::Create(req, res);

	std::shared_ptr<AnyPtrContainer> p=ctx;

	CHECK(p != nullptr);

}