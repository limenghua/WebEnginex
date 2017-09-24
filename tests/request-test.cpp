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

TEST(Request, Construct)
{
	RequestPtr res = Request::Create();

	//CHECK_TRUE(false);
}

TEST(Request, PutSomeValues)
{
	RequestPtr res = Request::Create();

	auto ptr = std::make_shared<int>(15);

	res->Put("age", ptr);

	auto val = res->Get<int>("age");

	CHECK_TRUE(val != nullptr);
	CHECK_TRUE(val == ptr);
	CHECK_EQUAL(*val, 15);
}

TEST(Request, PutSomeUserDefinedType)
{
	RequestPtr res = Request::Create();

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

TEST(Request, PutSomeUserDefinedTypeNoKeyName)
{
	RequestPtr res = Request::Create();

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

TEST(Request, GetNotExistValueShoudReturnNull)
{
	RequestPtr res = Request::Create();

	auto val = res->Get<int>("nothiskey");

	CHECK_TRUE(val == nullptr);
}
