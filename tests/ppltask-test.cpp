#include<CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include <ppltasks.h>


using concurrency::task;

TEST_GROUP(PPLTask)
{
	void teardown()
	{
		mock().clear();
	}

};

TEST(PPLTask, Constructor)
{
	mock().expectOneCall("myfun");

	auto r = task<void>([]() {
		mock().actualCall("myfun");
	}).then(
		[]() {return 100;}
	).then([](int a) {
		return a * 100;
	}).get();

	CHECK_EQUAL(r, 10000);
	mock().checkExpectations();
}