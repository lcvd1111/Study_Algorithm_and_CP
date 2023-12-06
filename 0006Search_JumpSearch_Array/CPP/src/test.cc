#include "test.hh"
#include "search.hh"

int UnitTest_RandomArray(void)
{
	ARRAY testArray;
	std::string testString = "lcvd_1111";

	testArray.AddRandom(30);
	testArray.Print();

	testArray.Sort();
	testArray.Print();

	testArray.ChangeRandomElement(testString, 777);
	testArray.Print();

	testArray.Sort();
	testArray.Print();

	return 0;
}

int UnitTest_Search(void)
{
	return 0;
}
