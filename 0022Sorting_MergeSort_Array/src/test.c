#include "test.h"
#define TEST_SIZE 1000

int UnitTest_Array(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, 100);
	testArray.Fill_Random(&testArray);
	//testArray.Print(&testArray);
	ARRAY_METHOD_DESTRUCTOR(&testArray);
	return 0;
}

int CustomCompare(const void *prev, const void *rear)
{
	int cmpResult = strcmp(((NODE *)prev)->name, ((NODE *)rear)->name);
	return cmpResult;
}

int UnitTest_Sort(void)
{
	NODE rawArray[TEST_SIZE];
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, TEST_SIZE);

	testArray.Fill_Random(&testArray);
	testArray.Copy_to_Raw_Array(&testArray, rawArray);

	testArray.Sort(&testArray);
	qsort(rawArray, TEST_SIZE, sizeof(NODE), CustomCompare);

	for (int i=0 ; i<TEST_SIZE ; i++){
		if (strcmp(rawArray[i].name, (testArray.nodeArray)[i].name))
			return (-1)*(i);
	}

	ARRAY_METHOD_DESTRUCTOR(&testArray);
	return 0;
}

int UnitTest_Sort_Iterative(void)
{
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
