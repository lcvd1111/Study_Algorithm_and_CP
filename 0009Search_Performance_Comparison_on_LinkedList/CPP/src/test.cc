#include "test.hh"
#include "search.hh"

int UnitTest_RandomList(void)
{
	LIST testList;
	std::string testString("lcvd_1111");

	testList.AddRandom(30);
	//testList.Print();

	testList.Sort();
	//testList.Print();

	testList.ChangeRandomElement(testString, 777);
	//testList.Print();

	testList.Sort();
	//testList.Print();

	return 0;
}

int UnitTest_LinearSearch(void)
{
	LIST testList;
	std::string testStr("lcvd_1111");

	testList.AddRandom(9006000);
	testList.ChangeRandomElement(testStr, 777);

	NODE &searchOut = testList.LinearSearch(testStr);
	if (strcmp(searchOut.name.c_str(), testStr.c_str()) != 0){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (searchOut.number != 777){
		UNIT_TEST_FAIL;
		return -2;
	}

	testStr = "T_E_S_T";
	NODE &searchOut2 = testList.LinearSearch(testStr);
	if (strcmp(searchOut2.name.c_str(), "SEARCH_FAIL") != 0){
		UNIT_TEST_FAIL;
		return -3;
	}

	return 0;
}

int UnitTest_JumpSearch(void)
{
	LIST testList;
	std::string testStr("lcvd_1111");

	testList.AddRandom(9006000);
	testList.ChangeRandomElement(testStr, 777);
	testList.Sort();

	if (FindSqrt(testList.size) != 3000){
		UNIT_TEST_FAIL;
		return -99;
	}

	NODE &searchOut = testList.JumpSearch(testStr);
	if (strcmp(searchOut.name.c_str(), testStr.c_str()) != 0){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (searchOut.number != 777){
		UNIT_TEST_FAIL;
		return -2;
	}
	testStr = "T_E_S_T";
	NODE &searchOut2 = testList.JumpSearch(testStr);
	if (strcmp(searchOut2.name.c_str(), "SEARCH_FAIL") != 0){
		UNIT_TEST_FAIL;
		return -3;
	}

	return 0;
}

int UnitTest_BinarySearch(void)
{
	return 0;
}

int UnitTest_TimeMeasurement(void)
{
	return 0;
}
