#include "test.hh"
#include "search.hh"

int UnitTest_RandomArray(void)
{
	ARRAY testArray;
	std::string testString = "lcvd_1111";

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

int UnitTest_Search(void)
{
	ARRAY testArray;
	std::string testString = "lcvd_1111";

	testArray.AddRandom(1000000);
	testArray.ChangeRandomElement(testString, 777);
	testArray.Sort();

	if (FindSqrt(testArray.Size()) != 1000){
		UNIT_TEST_FAIL;
		return -1;
	}

	NODE &searchResult = testArray.Search(testString);
	if (strcmp(searchResult.name.c_str(), "lcvd_1111") != 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchResult.number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}

	testString = "T_E_S_T";
	NODE &searchResult2 = testArray.Search(testString);
	if (strcmp(searchResult2.name.c_str(), "SEARCH_FAIL") != 0){
		UNIT_TEST_FAIL;
		return -4;
	}

	return 0;
}
