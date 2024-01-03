#include "test.h"
#include "array.h"

#define TEST_ARRAY_LEN 1000

int UnitTest_RandomArray(void)
{
	ARRAY testArray;

	ARRAY_CONSTRUCTOR(&testArray, 100);

	testArray.FillRandom(&testArray);
	//testArray.Print(&testArray);

	ARRAY_DESTRUCTOR(&testArray);

	return 0;
}

int CompareFunc(const void *front, const void *rear)
{
	int cmpResult = 0;

	cmpResult = strcmp(((NODE *)front)->name, ((NODE *)rear)->name);

	if (cmpResult > 0){
		//Swap
		return 1;
	}
	else if (cmpResult == 0){
		//Not Swap
		return 0;
	}
	else if (cmpResult < 0){
		//Not Swap
		return 0;
	}
}

int UnitTest_InsertionSort(void)
{
	ARRAY testArray;
	NODE testArray_For_Qsort[TEST_ARRAY_LEN];

	ARRAY_CONSTRUCTOR(&testArray, TEST_ARRAY_LEN);

	testArray.FillRandom(&testArray);
	memcpy(testArray_For_Qsort, testArray.nodeArray, sizeof(NODE)*TEST_ARRAY_LEN);

	testArray.Sort(&testArray);
	//testArray.Print(&testArray);
	qsort((void *)testArray_For_Qsort, TEST_ARRAY_LEN, sizeof(NODE), &CompareFunc);

	for (int i=0 ; i<testArray.Size(&testArray) ; i++){
		if ( strcmp((testArray.nodeArray)[i].name, testArray_For_Qsort[i].name)){
			return (-1)*(i);
		}
	}

	ARRAY_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest(void)
{
	int err = 0;

	err = UnitTest_RandomArray();
	if (err){
		printf(COLOR_BLACK "Unit Test for Creating Random Array: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for Creating Random Array: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	err = UnitTest_InsertionSort();
	if (err){
		printf(COLOR_BLACK "Unit Test for Insertion Sort: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -2;
	}
	printf(COLOR_BLACK "Unit Test for Insertion Sort: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	return 0;
}
