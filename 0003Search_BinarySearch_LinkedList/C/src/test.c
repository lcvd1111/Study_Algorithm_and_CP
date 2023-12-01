#include "test.h"
#include "search.h"

int UnitTest_RandomList(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);

	for (int i=0 ; i<10; i++){
		testList.AddRandom(&testList);
	}

	//testList.Print(&testList);

	testList.Sort(&testList);

	//testList.Print(&testList);

	testList.ChangeRandomElement(&testList, "lcvd1111", 777);

	//testList.Print(&testList);

	testList.Sort(&testList);

	//testList.Print(&testList);

	LIST_DESTRUCTOR(&testList);
	return 0;
}

int UnitTest_BinarySearch(void)
{
	NODE *searchOutput = NULL;
	LIST testList;
	LIST_CONSTRUCTOR(&testList);

	for (int i=0 ; i<100 ; i++){
		testList.AddRandom(&testList);
	}

	testList.ChangeRandomElement(&testList, "lcvd1111", 777);

	testList.Sort(&testList);

	searchOutput = testList.Search(&testList, "lcvd1111");
	if (strcmp(searchOutput->name, "lcvd1111") != 0){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (searchOutput->number != 777){
		UNIT_TEST_FAIL;
		return -2;
	}

	searchOutput = testList.Search(&testList, "T_E_S_T"); //LIST.name can't contain underbar.
	if (searchOutput != NULL){
		UNIT_TEST_FAIL;
		return -3;
	}

	testList.Print(&testList);
	LIST_DESTRUCTOR(&testList);
	return 0;
}
