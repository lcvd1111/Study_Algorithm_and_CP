#include "test.h"
#include "array.h"
#include "heap.h"

int UnitTest_Heap(void)
{
	NODE testNodes[5] = {{.name="c", .number=111}, {.name="a", .number=222}, {.name="e", .number=333}, {.name="d", .number=444}, {.name="b", .number=555}};
	PQ testPQ;
	PQ_CONSTRUCTOR(&testPQ, 10);

	testPQ.Enqueue(&testPQ, testNodes+0);
	if (testPQ.lastIndex != 0){
		UNIT_TEST_FAIL;
		return -1;
	}

	testPQ.Enqueue(&testPQ, testNodes+1);
	if (testPQ.lastIndex != 1){
		UNIT_TEST_FAIL;
		return -2;
	}

	testPQ.Enqueue(&testPQ, testNodes+2);
	if (testPQ.lastIndex != 2){
		UNIT_TEST_FAIL;
		return -3;
	}

	testPQ.Enqueue(&testPQ, testNodes+3);
	if (testPQ.lastIndex != 3){
		UNIT_TEST_FAIL;
		return -4;
	}

	testPQ.Enqueue(&testPQ, testNodes+4);
	if (testPQ.lastIndex != 4){
		UNIT_TEST_FAIL;
		return -5;
	}

	if (testPQ.Dequeue(&testPQ)->number != 222){
		UNIT_TEST_FAIL;
		return -6;
	}

	if (testPQ.Dequeue(&testPQ)->number != 555){
		UNIT_TEST_FAIL;
		return -6;
	}

	if (testPQ.Dequeue(&testPQ)->number != 111){
		UNIT_TEST_FAIL;
		return -6;
	}

	if (testPQ.Dequeue(&testPQ)->number != 444){
		UNIT_TEST_FAIL;
		return -6;
	}

	if (testPQ.Dequeue(&testPQ)->number != 333){
		UNIT_TEST_FAIL;
		return -6;
	}

	PQ_DESTRUCTOR(&testPQ);
	return 0;
}

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
	//Don't Swap
	return 0;
}

int UnitTest_HeapSort(void)
{
	ARRAY testArray;
	NODE* testArray_qsort = NULL;
	int testSize = 1000;
	ARRAY_CONSTRUCTOR(&testArray, testSize);

	testArray.FillRandom(&testArray);

	testArray_qsort = (NODE *)malloc(sizeof(NODE)*(testSize));

	memcpy(testArray_qsort, testArray.nodeArray, sizeof(NODE)*testSize);

	testArray.Sort(&testArray);
	qsort(testArray_qsort, testSize, sizeof(NODE), &CompareFunc);

	for (int i=0 ; i<testSize ; i++){
		if (strcmp(testArray.nodeArray[i].name, testArray_qsort[i].name)){
			return (-1)*(i);
		}
	}

	//testArray.Print(&testArray);

	free(testArray_qsort);
	ARRAY_DESTRUCTOR(&testArray);
	return 0;
}

int UnitTest(void)
{
	int err = 0;

	err = UnitTest_Heap();
	printf(COLOR_BLACK "Unit Test for Priority Queue using Heap: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "FAIL.\n" COLOR_BLACK );
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d\n" COLOR_BLACK, err);
	}
	printf(COLOR_GREEN "SUCCESS.\n" COLOR_BLACK);

	err = UnitTest_Array();
	printf(COLOR_BLACK "Unit Test for Creating Random Array: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "FAIL.\n" COLOR_BLACK );
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d\n" COLOR_BLACK, err);
	}
	printf(COLOR_GREEN "SUCCESS.\n" COLOR_BLACK);

	err = UnitTest_HeapSort();
	printf(COLOR_BLACK "Unit Test for Heap Sort on Array: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "FAIL.\n" COLOR_BLACK );
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d\n" COLOR_BLACK, err);
	}
	printf(COLOR_GREEN "SUCCESS.\n" COLOR_BLACK);

	return 0;
}
