#include<CppUTest/TestHarness.h>
#include<enginex/any-container.h>

using namespace enginex;

TEST_GROUP(AnyPtrContainer)
{

};


TEST(AnyPtrContainer, constructor)
{
	AnyPtrContainer anyPtrContainer;
}

TEST(AnyPtrContainer, PutShared)
{
	AnyPtrContainer anyPtrContainer;
	auto ptr = std::make_shared<int>(5);
	anyPtrContainer.Set("age", ptr);

	CHECK_EQUAL(ptr.use_count(), 2);
	CHECK_TRUE(anyPtrContainer.Get<int>("age")== ptr);
	CHECK_EQUAL(*(anyPtrContainer.Get<int>("age")), 5);
}

TEST(AnyPtrContainer, PutNoShared)
{
	AnyPtrContainer anyPtrContainer;

	int a;
	std::string b;
	double c;
	class AnyOtherTypeNoSharedPtr {

	};
	//AnyOtherTypeNoSharedPtr someType;

	//anyPtrContainer.Set("a", a);    //无法通过编译
	anyPtrContainer.Set("a", std::make_shared<int>(a));
	//anyPtrContainer.Set("b", b);    //无法通过编译
	anyPtrContainer.Set("b", std::make_shared<std::string>(b));
	//anyPtrContainer.Set("c", c);   //无法通过编译
	anyPtrContainer.Set("b", std::make_shared<double>(c));
	//anyPtrContainer.Set("someType", someType);   //无法通过编译
	anyPtrContainer.Set("someType", std::make_shared<AnyOtherTypeNoSharedPtr>());
}

TEST(AnyPtrContainer, WeakPtr)
{
	AnyPtrContainer anyPtrContainer;
	auto ptr = std::make_shared<int>(5);
	auto weakPtr = std::weak_ptr<int>(ptr);
	anyPtrContainer.Set("age", weakPtr);

	CHECK_EQUAL(ptr.use_count(), 1);
	CHECK_TRUE(anyPtrContainer.Get<int>("age")== ptr);
	CHECK_EQUAL(*(anyPtrContainer.Get<int>("age")), 5);
}


TEST(AnyPtrContainer, Get)
{
	AnyPtrContainer anyPtrContainer;
	auto ptr = std::make_shared<std::string>("hello world");
	anyPtrContainer.Set("hello", ptr);

	CHECK_TRUE(anyPtrContainer.Get<std::string>("hello")== ptr);
	CHECK_EQUAL(*(anyPtrContainer.Get<std::string>("hello")), "hello world");
}

TEST(AnyPtrContainer, Delete)
{
	AnyPtrContainer anyPtrContainer;
	auto ptr = std::make_shared<std::string>("hello world");
	anyPtrContainer.Set("hello", ptr);

	CHECK_TRUE(anyPtrContainer.Get<std::string>("hello")== ptr);
	CHECK_EQUAL(*(anyPtrContainer.Get<std::string>("hello")), "hello world");

	anyPtrContainer.Delete("hello");
	ptr = anyPtrContainer.Get<std::string>("hello");
	CHECK_FALSE(ptr);
}