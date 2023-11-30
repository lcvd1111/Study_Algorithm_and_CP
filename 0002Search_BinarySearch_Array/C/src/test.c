#include "test.h"
#include "search.h"

int UnitTest_RandomArray(void)
{
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 10);
	testArray.FillRandom(&testArray);
	//testArray.Print(&testArray);
	//printf("\n");

	testArray.Sort(&testArray);
	//testArray.Print(&testArray);
	//printf("\n");

	testArray.ChangeRandomElement(&testArray, "lcvd1111", 7777);
	//testArray.Print(&testArray);
	//printf("\n");

	testArray.Sort(&testArray);
	//testArray.Print(&testArray);
	//printf("\n");

	ARRAY_DESTRUCTOR(&testArray);
	ARRAY_CONSTRUCTOR(&testArray, 10);
	testArray.FillRandom(&testArray);
	ARRAY_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest_BinarySearch(void)
{
	NODE *searchResult = NULL;
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 1000000);

	testArray.FillRandom(&testArray);

	testArray.ChangeRandomElement(&testArray, "lcvd1111", 7777);

	testArray.Sort(&testArray);

	searchResult = testArray.Search(&testArray, "lcvd1111");

	if (searchResult == NULL){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (strcmp(searchResult->name, "lcvd1111") != 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchResult->number != 7777){
		UNIT_TEST_FAIL;
		return -3;
	}

	searchResult = testArray.Search(&testArray, "T_E_S_T"); //Underbar can't exist in the name.
	if (searchResult != NULL){
		UNIT_TEST_FAIL;
		return -4;
	}

	ARRAY_DESTRUCTOR(&testArray);
	return 0;
}
