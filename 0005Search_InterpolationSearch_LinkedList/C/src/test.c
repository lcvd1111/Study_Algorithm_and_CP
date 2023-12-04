#include "test.h"
#include "search.h"

int UnitTest_RandomList(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);

	for (int i=0 ; i<10 ; i++){
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

int UnitTest_InterpolationSearch(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);
	NODE *searchOut = NULL;

	for (int i=0 ; i<10000 ; i++){
		testList.AddRandom(&testList);
	}
	testList.ChangeRandomElement(&testList, "lcvd1111", 777);
	testList.Sort(&testList);

	//testList.Print(&testList);
	
	searchOut = testList.Search(&testList, 777);
	if (searchOut == NULL){
		UNIT_TEST_FAIL;
		printf(COLOR_CYAN "%s, %d\n", searchOut->name, searchOut->number);
		return -1;
	}

	if (strcmp(searchOut->name, "lcvd1111") != 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchOut->number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}

	searchOut = testList.Search(&testList, 777777);
	if (searchOut != NULL){
		UNIT_TEST_FAIL;
		return -4;
	}

	LIST_DESTRUCTOR(&testList);
	return 0;
}
