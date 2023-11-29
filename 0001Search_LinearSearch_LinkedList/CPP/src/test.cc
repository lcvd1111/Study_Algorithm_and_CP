#include "test.hh"
#include "search.hh"

int UnitTest_RandomList(void)
{
	LIST *testList = new LIST;

	(*testList).AddRandom(100);
	//(*testList).Print();

	delete testList;

	testList = new LIST;

	(*testList).AddRandom(10);
	//(*testList).Print();

	delete testList;

	return 0;
}

int UnitTest_LinearSearch(void)
{
	LIST testList;
	NODE *searchResult = NULL;
	std::string tempName;

	testList.AddRandom(50000);
	tempName = "lcvd1111";
	testList.ChangeRandomElement(tempName, 77777);
	//testList.Print();
	searchResult = testList.Search(tempName);
	if (searchResult == NULL){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (searchResult->name != tempName){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchResult->number != 77777){
		UNIT_TEST_FAIL;
		return -3;
	}

	tempName = "T_E_S_T";
	searchResult = testList.Search(tempName);
	
	if (searchResult != NULL){
		UNIT_TEST_FAIL;
		return -4;
	}
	return 0;
}
