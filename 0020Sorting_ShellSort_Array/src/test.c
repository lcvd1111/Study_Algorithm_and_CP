#include "test.h"

int UnitTest_Array(void)
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
	else {
		//Don't Swap
		return 0;
	}
}

int UnitTest_Sort(void)
{
	ARRAY testArray;
	NODE *testArray_for_Qsort = NULL;
	ARRAY_CONSTRUCTOR(&testArray, 20000);

	testArray.FillRandom(&testArray);
	testArray.CopyRawArray(&testArray, &testArray_for_Qsort);

	//testArray.Print(&testArray);
	
	testArray.Sort(&testArray);
	qsort(testArray_for_Qsort, testArray.size, sizeof(NODE), &CompareFunc);

	for (int i=0 ; i<testArray.size ; i++){
		if (strcmp(testArray.nodeArray[i].name, testArray_for_Qsort[i].name)){
			return -1;
		}
	}

	//testArray.Print(&testArray);

	ARRAY_DESTRUCTOR(&testArray);
	free(testArray_for_Qsort);

	return 0;
}

int UnitTest(void)
{
	int err = 0;
	
	err = UnitTest_Array();
	printf(COLOR_BLACK "Unit Test for Creating Random Array: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "FAIL.\n"
				COLOR_BLACK "Error Code: "
				COLOR_RED "%d\n"
				COLOR_BLACK , err);
		return -1;
	}
	printf(COLOR_GREEN "SUCCESS.\n");

	err = UnitTest_Sort();
	printf(COLOR_BLACK "Unit Test for Shell Sort on Array: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "FAIL.\n"
				COLOR_BLACK "Error Code: "
				COLOR_RED "%d\n"
				COLOR_BLACK , err);
		return -2;
	}
	printf(COLOR_GREEN "SUCCESS.\n");

	return 0;
}
