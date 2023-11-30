#include "test.hh"
#include "search.hh"

int UnitTest_RandomArray(void)
{
	std::string testString = "lcvd1111";
	ARRAY testArray;
	testArray.AddRandom(100);
	testArray.Print();
	std::cout << std::endl;
	testArray.Sort();
	testArray.Print();
	std::cout << std::endl;
	testArray.ChangeRandomElement(testString, 77777);
	testArray.Print();
	std::cout << std::endl;
	testArray.Sort();
	testArray.Print();
	return 0;
}

int UnitTest_BinarySearch(void)
{
	return 0;
}
