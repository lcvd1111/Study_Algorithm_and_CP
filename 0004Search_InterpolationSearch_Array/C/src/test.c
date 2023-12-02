#include "test.h"
#include "search.h"

int UnitTest_RandomArray(void)
{
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 10);

	testArray.FillRandom(&testArray);
	//testArray.Print(&testArray);

	testArray.Sort(&testArray);
	//testArray.Print(&testArray);

	testArray.ChangeRandomElement(&testArray, "lcvd1111", 777);
	//testArray.Print(&testArray);

	testArray.Sort(&testArray);
	//testArray.Print(&testArray);

	ARRAY_DESTRUCTOR(&testArray);
	return 0;
}

int UnitTest_InterpolationSearch(void)
{
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 100);
	NODE *searchResult = NULL;


	testArray.FillRandom(&testArray);
	testArray.ChangeRandomElement(&testArray, "lcvd1111", 777);
	testArray.Sort(&testArray);

	searchResult = testArray.Search(&testArray, 777);

	if (searchResult == NULL){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (strcmp(searchResult->name, "lcvd1111") != 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchResult->number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}

	searchResult = testArray.Search(&testArray, 999999);
	if (searchResult != NULL){
		UNIT_TEST_FAIL;
		return -4;
	}

	ARRAY_DESTRUCTOR(&testArray);
	return 0;
}
