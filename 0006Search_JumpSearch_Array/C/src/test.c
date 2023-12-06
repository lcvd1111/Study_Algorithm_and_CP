#include "test.h"
#include "search.h"

int UnitTest_RandomArray(void)
{
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 300);

	testArray.FillRandom(&testArray);
	//testArray.Print(&testArray);

	testArray.Sort(&testArray);
	//testArray.Print(&testArray);

	testArray.ChangeRandomElement(&testArray, "lcvd_1111", 777);
	//testArray.Print(&testArray);

	testArray.Sort(&testArray);
	//testArray.Print(&testArray);

	ARRAY_DESTRUCTOR(&testArray);
	return 0;
}

int UnitTest_JumpSearch(void)
{
	ARRAY testArray;
	NODE *searchOut = NULL;

	ARRAY_CONSTRUCTOR(&testArray, 1000000);

	if (FindSqrt(testArray.size) != 1000){
		UNIT_TEST_FAIL;
		return -99;
	}

	testArray.FillRandom(&testArray);
	testArray.ChangeRandomElement(&testArray, "lcvd_1111", 777);
	testArray.Sort(&testArray);
	searchOut = testArray.Search(&testArray, "lcvd_1111");

	if (searchOut == NULL){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (strcmp(searchOut->name, "lcvd_1111") != 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchOut->number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}

	searchOut = testArray.Search(&testArray, "@@@");
	if (searchOut != NULL){
		UNIT_TEST_FAIL;
		return -4;
	}

	return 0;
}
