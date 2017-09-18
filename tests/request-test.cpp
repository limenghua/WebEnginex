#include<CppUTest/TestHarness.h>

TEST_GROUP(Request)
{

};

TEST(Request, construct)
{
	STRCMP_EQUAL("hello", "hello");
}