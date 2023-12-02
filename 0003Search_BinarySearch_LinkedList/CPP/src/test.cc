#include "test.hh"
#include "search.hh"

int UnitTest_RandomList(void)
{
	LIST testList;
	std::string testString = "lcvd1111";
	testList.AddRandom(100);
	//testList.Print();

	testList.Sort();
	//testList.Print();

	testList.ChangeRandomElement(testString, 777);
	//testList.Print();

	testList.Sort();
	//testList.Print();

	return 0;
}

int UnitTest_BinarySearch(void)
{
	LIST testList;
	std::string testString = "lcvd1111";

	testList.AddRandom(10000);
	testList.ChangeRandomElement(testString, 777);
	testList.Sort();

	NODE &searchResult = testList.Search(testString);
	if (strcmp(searchResult.name.c_str(), testString.c_str())){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (searchResult.number != 777){
		UNIT_TEST_FAIL;
		return -2;
	}

	testString = "T_E_S_T";
	if (strcmp(testList.Search(testString).name.c_str(), "SEARCH_FAIL")){
		UNIT_TEST_FAIL;
		return -3;
	}

	return 0;
}
