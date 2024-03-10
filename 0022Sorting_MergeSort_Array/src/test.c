#include "test.h"

int UnitTest_Array(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, 100);
	testArray.Fill_Random(&testArray);
	//testArray.Print(&testArray);
	ARRAY_METHOD_DESTRUCTOR(&testArray);
	return 0;
}

int UnitTest_Sort(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, 4);

	testArray.Fill_Random(&testArray);
	testArray.Print(&testArray);

	testArray.Sort(&testArray);
	printf("\n");
	testArray.Print(&testArray);

	ARRAY_METHOD_DESTRUCTOR(&testArray);
	return 0;
}

int UnitTest(void)
{
	if (UnitTest_Array()){
		printf(COLOR_BLACK "Unit Test for Array: " COLOR_RED "FAIL\n" COLOR_BLACK);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for Array: " COLOR_GREEN "SUCCESS\n" COLOR_BLACK);

	if (UnitTest_Sort()){
		printf(COLOR_BLACK "Unit Test for Merge Sort on array: " COLOR_RED "FAIL\n" COLOR_BLACK);
		return -2;
	}
	printf(COLOR_BLACK "Unit Test for Merge Sort on array: " COLOR_GREEN "SUCCESS\n" COLOR_BLACK);

	return 0;
}
