#include "test.hh"
#include "search.hh"

int UnitTest_RandomList(void)
{
	LIST testList;
	std::string testString("lcvd1111");

	testList.AddRandom(10);
	//testList.Print();

	testList.Sort();
	//testList.Print();

	testList.ChangeRandomElement(testString, 777);
	//testList.Print();
	
	testList.Sort();
	//testList.Print();

	return 0;
}

int UnitTest_InterpolationSearch(void)
{
	LIST testList;
	std::string testString("lcvd1111");

	testList.AddRandom(100000);
	testList.ChangeRandomElement(testString, 5555);
	testList.Sort();

	//testList.Print();

	NODE &searchOut = testList.Search(5555);
	if (strcmp(searchOut.name.c_str(), "SEARCH_FAIL") == 0){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (strcmp(searchOut.name.c_str(), "lcvd1111") != 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchOut.number != 5555){
		UNIT_TEST_FAIL;
		return -3;
	}

	NODE &searchOut2 = testList.Search(77777);
	if (strcmp(searchOut2.name.c_str(), "SEARCH_FAIL") != 0){
		UNIT_TEST_FAIL;
		return -4;
	}
	
	return 0;
}
