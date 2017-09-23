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

TEST(Message, AppendHeader)
{
	Message msg;
	msg.AppendHeader("key1", "value1");

	CHECK_TRUE( ! msg.GetHeaders().empty());
	CHECK_EQUAL(msg.GetHeader("key1"), "value1");
}
