#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include<enginex/message.h>
using enginex::Message;

TEST_GROUP(Message)
{
};

TEST(Message, EmptyConstruct)
{
	Message msg;
	CHECK_EQUAL(msg.GetBody(), "");
	CHECK_EQUAL(msg.GetVersion(), "");
	CHECK_TRUE(msg.GetHeaders().empty());
}

TEST(Message, SetHeader)
{
	Message msg;
	msg.SetHeader("key1", "value1");

	CHECK_TRUE( ! msg.GetHeaders().empty());
	CHECK_EQUAL(msg.GetHeader("key1"), "value1");
}

template<class C, class T>
auto contains(const C& v, const T& x)
-> bool
{
	return end(v) != std::find(begin(v), end(v), x);
}

TEST(Message, AppendHeader)
{
	Message msg;
	msg.SetHeader("key1", "value1");
	msg.AppendHeader("key1", "value2");

	auto values = msg.GetHeaders("key1");
	CHECK_EQUAL(values.size(), 2);

	CHECK_TRUE(contains(values, "value1"));
	CHECK_TRUE(contains(values, "value2"));

}
