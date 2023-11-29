#include "test.h"
#include "search.h"

int UnitTest_RandomList(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);

	for (int i=0 ; i<100; i++){
		testList.AddRandom(&testList);
	}

	//testList.Print(&testList);
	//printf("\n");
	
	testList.Clear(&testList);

	for (int i=0 ; i<10; i++){
		testList.AddRandom(&testList);
	}
	testList.Change(&testList, "lcvd1111", 12345);
	//testList.Print(&testList);

	testList.Clear(&testList);
	LIST_DESTRUCTOR(&testList);

	return 0;
}

int UnitTest_Search(void)
{
	LIST testList;
	NODE *searchResult;
	LIST_CONSTRUCTOR(&testList);

	for (int i=0 ; i<60000; i++){
		testList.AddRandom(&testList);
	}

	testList.Change(&testList, "lcvd1111", 12345);
	searchResult = testList.Search(&testList, "lcvd1111");

	if (searchResult == NULL){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (strcmp(searchResult->name, "lcvd1111") != 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchResult->number != 12345){
		UNIT_TEST_FAIL;
		return -3;
	}

	searchResult = testList.Search(&testList, "impossible_name");
	if (searchResult != NULL){
		UNIT_TEST_FAIL;
		return -4;
	}

	LIST_DESTRUCTOR(&testList);

	return 0;
}
