#include "test.h"

int UnitTest_RandomArray(void)
{
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 100);

	testArray.FillRandom(&testArray);
	//testArray.Print(&testArray);

	testArray.ChangeRandomElement(&testArray, "lcvd1111", 777);
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

int UnitTest_SelectionSort(void)
{
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 1000);
	NODE testArray_for_Qsort[1000];

	testArray.FillRandom(&testArray);
	testArray.ChangeRandomElement(&testArray, "lcvd1111", 777);

	memcpy(testArray_for_Qsort, testArray.nodeArray, sizeof(NODE)*1000);

	testArray.Sort(&testArray);

	qsort(testArray_for_Qsort, 1000, sizeof(NODE), &CompareFunc);

	for (int i=0 ; i<1000 ; i++){
		if (strcmp(testArray_for_Qsort[i].name, testArray.nodeArray[i].name) != 0){
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
	printf(COLOR_BLACK "Unit Test for Creating Random Array: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "Fail\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d\n" COLOR_BLACK, err);
		return -1;
	}
	printf(COLOR_GREEN "Success\n" COLOR_BLACK );

	err = UnitTest_SelectionSort();
	printf(COLOR_BLACK "Unit Test for Selection Sort on an Array: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "Fail\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d\n" COLOR_BLACK, err);
		return -2;
	}
	printf(COLOR_GREEN "Success\n" COLOR_BLACK );
	return 0;
}
