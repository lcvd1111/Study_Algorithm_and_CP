#include "test.h"
#include "search.h"

int UnitTest_RandomList(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);

	for (int i=0 ; i<300 ; i++){
		testList.AddRandom(&testList);
	}
	//testList.Print(&testList);

	testList.Sort(&testList);
	//testList.Print(&testList);

	testList.ChangeRandomElement(&testList, "lcvd_1111", 777);
	//testList.Print(&testList);

	testList.Sort(&testList);
	//testList.Print(&testList);

	LIST_DESTRUCTOR(&testList);
	return 0;
}

int UnitTest_JumpSearch(void)
{
	LIST testList;
	NODE *searchOut = NULL;

	LIST_CONSTRUCTOR(&testList);

	for (int i=0; i<1002000 ; i++){
		testList.AddRandom(&testList);
	}

	if (testList.size != 1002000){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (FindSqrt(testList.size) != 1000){
		UNIT_TEST_FAIL;
		return -2;
	}

	testList.ChangeRandomElement(&testList, "lcvd_1111", 777);
	testList.Sort(&testList);
	
	searchOut = testList.Search(&testList, "lcvd_1111");
	
	if (strcmp(searchOut->name, "lcvd_1111") != 0){
		UNIT_TEST_FAIL;
		return -3;
	}

	if (searchOut->number != 777){
		UNIT_TEST_FAIL;
		return -4;
	}

	searchOut = testList.Search(&testList, "T_E_S_T");
	if (searchOut != NULL){
		UNIT_TEST_FAIL;
		return -5;
	}

	return 0;
}
