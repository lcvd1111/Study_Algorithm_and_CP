#include "test.h"
#include "array.h"

int UnitTest_RandomArray(void)
{
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 10);
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

	if (cmpResult == 0){
		return 0;
	}
	else if (cmpResult > 0){
		return 1;
	}
	return 0;
}

int UnitTest_BubbleSort(void)
{
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 1000);
	NODE *testBuffer = NULL;

	testArray.FillRandom(&testArray);
	testBuffer = (NODE *)malloc(sizeof(NODE)*(testArray.size));
	memcpy(testBuffer, testArray.array, sizeof(NODE)*(testArray.size));

	//testArray.Print(&testArray);

	qsort(testBuffer, testArray.size, sizeof(NODE), &CompareFunc);
	testArray.Sort(&testArray);

	//testArray.Print(&testArray);

	for (int i=0 ; i<testArray.size ; i++){
		if (strcmp(testArray.array[i].name, testBuffer[i].name) != 0){
			free(testBuffer);
			ARRAY_DESTRUCTOR(&testArray);
			return -1;
		}
	}
	
	free(testBuffer);
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

	err = UnitTest_BubbleSort();
	if (err){
		printf(COLOR_BLACK "Unit Test for Bubble Sort: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -2;
	}
	printf(COLOR_BLACK "Unit Test for Bubble Sort: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	return 0;
}
