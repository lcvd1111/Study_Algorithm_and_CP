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
	else {
		//Don't Swap
		return 0;
	}
}

int UnitTest_SelectionSort(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);
	int testSize = 1000;
	NODE *testArray = NULL;
	NODE *tempNode = NULL;

	for (int i=0 ; i<testSize ; i++){
		testList.AddRandom(&testList);
	}

	testList.ChangeRandomElement(&testList, "lcvd1111", 777);
	testList.CopyArray(&testList, &testArray);

	testList.Sort(&testList);

	qsort(testArray, testSize, sizeof(NODE), &CompareFunc);

	tempNode = testList.begin;
	for (int i=0 ; i<testSize ; i++){
		if (strcmp(tempNode->name, testArray[i].name)){
			return -1;
		}
		tempNode = tempNode->next;
	}

	//testList.Print(&testList);

	LIST_DESTRUCTOR(&testList);
	free(testArray);
	return 0;
}

int UnitTest(void)
{
	int err = 0;

	err = UnitTest_RandomList();
	printf(COLOR_BLACK "Unit Test for Creating Random List: ");
	if (err){
		printf(COLOR_RED "Fail\n");
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d\n", err);
		return -1;
	}
	printf(COLOR_GREEN "Success\n");

	err = UnitTest_SelectionSort();
	printf(COLOR_BLACK "Unit Test for Selection Sort to Linked List: ");
	if (err){
		printf(COLOR_RED "Fail\n");
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d\n", err);
		return -2;
	}
	printf(COLOR_GREEN "Success\n");
	return 0;
}
