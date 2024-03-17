#include "test.h"

int UnitTest_Heap(void)
{
	NODE nodeArray[] = {{.name="bbb", .number=111}, {.name="ddd", .number=222}, {.name="aaa", .number=333}, {.name="eee", .number=444}, {.name="ccc", .number=555}};
	PQ testPQ;
	PQ_CONSTRUCTOR(&testPQ, 10);

	testPQ.Enqueue(&testPQ, nodeArray+0);
	if (testPQ.lastIndex != 0){
		UNIT_TEST_FAIL;
		return -1;
	}

	testPQ.Enqueue(&testPQ, nodeArray+1);
	if (testPQ.lastIndex != 1){
		UNIT_TEST_FAIL;
		return -2;
	}

	testPQ.Enqueue(&testPQ, nodeArray+2);
	if (testPQ.lastIndex != 2){
		UNIT_TEST_FAIL;
		return -3;
	}

	testPQ.Enqueue(&testPQ, nodeArray+3);
	if (testPQ.lastIndex != 3){
		UNIT_TEST_FAIL;
		return -4;
	}

	testPQ.Enqueue(&testPQ, nodeArray+4);
	if (testPQ.lastIndex != 4){
		UNIT_TEST_FAIL;
		return -5;
	}

	if (testPQ.Dequeue(&testPQ)->number != 333){
		UNIT_TEST_FAIL;
		return -6;
	}

	if (testPQ.Dequeue(&testPQ)->number != 111){
		UNIT_TEST_FAIL;
		return -7;
	}

	if (testPQ.Dequeue(&testPQ)->number != 555){
		UNIT_TEST_FAIL;
		return -8;
	}

	if (testPQ.Dequeue(&testPQ)->number != 222){
		UNIT_TEST_FAIL;
		return -9;
	}

	if (testPQ.Dequeue(&testPQ)->number != 444){
		UNIT_TEST_FAIL;
		return -10;
	}

	PQ_DESTRUCTOR(&testPQ);
	return 0;
}

int UnitTest_List(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);

	for (int i=0 ; i<100 ; i++){
		testList.AddRandom(&testList);
	}

	//testList.Print(&testList);

	LIST_DESTRUCTOR(&testList);
	return 0;
}

int CompareFunc(const void *front, const void *rear)
{
	int cmpResult = 0;

	cmpResult = strcmp(((NODE *)front)->name, ((NODE *)rear)->name);

	if (cmpResult>0){
		//Swap
		return 1;
	}
	//Don't Swap
	return 0;
}

int UnitTest_HeapSort(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);
	int testSize = 1000;
	NODE *testArray_qsort = NULL;
	NODE *temp = NULL;

	for (int i=0 ; i<testSize ; i++){
		testList.AddRandom(&testList);
	}
	testList.CopyArray(&testList, &testArray_qsort);

	testList.Sort(&testList);
	qsort(testArray_qsort, testSize, sizeof(NODE), &CompareFunc);

	temp = testList.begin;

	for (int i=0 ; i<testList.size ; i++){
		if(strcmp(testArray_qsort[i].name, temp->name)){
			return -1;
		}
		temp = temp->next;
	}

	//testList.Print(&testList);

	LIST_DESTRUCTOR(&testList);
	free(testArray_qsort);
	return 0;
}

int UnitTest(void)
{
	int err = 0;

	err = UnitTest_Heap();
	printf(COLOR_BLACK "Unit Test for Binry Heap: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "FAIL.\n" COLOR_BLACK);
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d\n" COLOR_BLACK, err);
	}
	printf(COLOR_GREEN "SUCCESS.\n" COLOR_BLACK);

	err = UnitTest_List();
	printf(COLOR_BLACK "Unit Test for Linked List: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "FAIL.\n" COLOR_BLACK);
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d\n" COLOR_BLACK, err);
	}
	printf(COLOR_GREEN "SUCCESS.\n" COLOR_BLACK);

	err = UnitTest_HeapSort();
	printf(COLOR_BLACK "Unit Test for Heapsort on Linked List: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "FAIL.\n" COLOR_BLACK);
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d\n" COLOR_BLACK, err);
	}
	printf(COLOR_GREEN "SUCCESS.\n" COLOR_BLACK);

	return 0;
}
