#include "test.hh"
#include "search.hh"

int UnitTest_RandomArray(void)
{
	std::string testString = "lcvd1111";
	ARRAY testArray;
	testArray.AddRandom(30);
	//testArray.Print();
	testArray.Sort();
	//testArray.Print();
	testArray.ChangeRandomElement(testString, 777);
	//testArray.Print();
	testArray.Sort();
	//testArray.Print();

	return 0;
}

int UnitTest_InterpolationSearch(void)
{
	std::string testString = "lcvd1111";
	ARRAY testArray;
	testArray.AddRandom(100);
	testArray.ChangeRandomElement(testString, 777);
	testArray.Sort();

	NODE &searchOut = testArray.Search(777);
	if (strcmp(searchOut.name.c_str(), "SEARCH_FAIL") == 0){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (strcmp(searchOut.name.c_str(), "lcvd1111")){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchOut.number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}

	NODE &searchOut2 = testArray.Search(99999999);
	if (strcmp(searchOut2.name.c_str(), "SEARCH_FAIL") != 0){
		UNIT_TEST_FAIL;
		return -4;
	}

	return 0;
}
