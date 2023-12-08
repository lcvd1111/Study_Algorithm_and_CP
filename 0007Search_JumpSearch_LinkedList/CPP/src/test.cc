#include "test.hh"
#include "search.hh"

int UnitTest_RandomList(void)
{
	LIST testList;
	std::string testStr("lcvd_1111");

	testList.AddRandom(1000);
	//testList.Print();

	testList.Sort();
	//testList.Print();

	testList.ChangeRandomElement(testStr, 777);
	//testList.Print();

	testList.Sort();
	//testList.Print();

	return 0;
}

int UnitTest_JumpSearch(void)
{
	LIST testList;
	std::string testStr("lcvd_1111");

	testList.AddRandom(9006000);
	testList.ChangeRandomElement(testStr, 777);
	testList.Sort();

	if (FindSqrt(testList.Size()) != 3000){
		UNIT_TEST_FAIL;
		return -1;
	}

	NODE &searchResult = testList.Search(testStr);
	if (strcmp(searchResult.name.c_str(), testStr.c_str()) != 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchResult.number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}

	testStr = "T_E_S_T";
	NODE &searchResult2 = testList.Search(testStr);

	if (strcmp(searchResult2.name.c_str(), "SEARCH_FAIL") != 0){
		UNIT_TEST_FAIL;
		return -4;
	}

	return 0;
}
