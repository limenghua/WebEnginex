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

TEST(Response, PutSomeValues)
{
	ResponsePtr res = Response::Create();

	auto ptr = std::make_shared<int>(15);

	res->Put("age", ptr);

	auto val = res->Get<int>("age");

	CHECK_TRUE(val != nullptr);
	CHECK_TRUE(val==ptr);
	CHECK_EQUAL(*val, 15);
}

TEST(Response, PutSomeUserDefinedType)
{
	ResponsePtr res = Response::Create();

	struct MyStruct
	{
		int a;
		char b;
	};

	auto ptr = std::make_shared<MyStruct>();
	ptr->a = 3;
	ptr->b = 'b';

	res->Put("MyStruct", ptr);

	auto val = res->Get<MyStruct>("MyStruct");

	CHECK_TRUE(val != nullptr);
	CHECK_TRUE(val == ptr);
	CHECK_EQUAL(val->a, 3);
}

TEST(Response, PutSomeUserDefinedTypeNoKeyName)
{
	ResponsePtr res = Response::Create();

	struct MyStruct
	{
		int a;
		char b;
	};

	auto ptr = std::make_shared<MyStruct>();
	ptr->a = 3;
	ptr->b = 'b';

	res->Put(ptr);

	auto val = res->Get<MyStruct>();

	CHECK_TRUE(val != nullptr);
	CHECK_TRUE(val == ptr);
	CHECK_EQUAL(val->a, 3);
}

TEST(Response, GetNotExistValueShoudReturnNull)
{
	ResponsePtr res = Response::Create();

	auto val = res->Get<int>("nothiskey");

	CHECK_TRUE(val == nullptr);
}
