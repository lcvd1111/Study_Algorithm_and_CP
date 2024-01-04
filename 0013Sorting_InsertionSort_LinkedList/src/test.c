#include "test.h"
#include "list.h"

int UnitTest_RandomList(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);

	for (int i=0 ; i<100 ; i++){
		testList.AddRandom(&testList);
	}

	//testList.Print(&testList);

	testList.ChangeRandomElement(&testList, "lcvd1111", 777);
	//testList.Print(&testList);

	LIST_DESTRUCTOR(&testList);

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
	if (cmpResult == 0){
		//Don't Swap
		return 0;
	}
	if (cmpResult < 0){
		//Don't Swap
		return 0;
	}
}

int UnitTest_InsertionSort(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);
	NODE *testArray = NULL;
	NODE *traversalNode = NULL;

	for (int i=0 ; i<2000 ; i++){
		testList.AddRandom(&testList);
	}

	testList.ChangeRandomElement(&testList, "lcvd1111", 777);

	testList.Sort(&testList);
	//testList.Print(&testList);

	testList.CopyArray(&testList, &testArray);
	qsort(testArray, testList.size, sizeof(NODE), &CompareFunc);

	traversalNode = testList.begin;
	for (int i=0; i<(testList.size) ; i++){
		if (strcmp((testArray+i)->name, traversalNode->name)){
			printf("Name1: %s, Name2: %s\n", (testArray+i)->name, traversalNode->name);
			return (-1)*(i);
		}
		traversalNode = traversalNode -> next;
	}

	LIST_DESTRUCTOR(&testList);
	free(testArray);

	return 0;
}

int UnitTest(void)
{
	int err = 0;

	err = UnitTest_RandomList();
	printf(COLOR_BLACK "Unit Test for Creating RandomList: ");
	if (err){
		printf(COLOR_RED "Fail.\n" COLOR_BLACK);
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d\n" COLOR_BLACK, err);
		return -1;
	}
	printf(COLOR_GREEN "Success.\n" COLOR_BLACK);

	err = UnitTest_InsertionSort();
	printf(COLOR_BLACK "Unit Test for Insertion Sort toward linked list: ");
	if (err){
		printf(COLOR_RED "Fail.\n" COLOR_BLACK);
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d\n" COLOR_BLACK, err);
		return -2;
	}
	printf(COLOR_GREEN "Success.\n" COLOR_BLACK);

	return 0;
}
