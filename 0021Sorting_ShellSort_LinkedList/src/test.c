#include "test.h"

int UnitTest_List(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);

	NODE *testArray = NULL;

	for (int i=0 ; i<100 ; i++){
		testList.AddRandom(&testList);
	}
	testList.CopyRawArray(&testList, &testArray);

	/*
	testList.Print(&testList);

	for (int i=0 ; i<testList.size ; i++){
		printf("[%d] Name: %s, Number: %d\n", i, testArray[i].name, testArray[i].number);
	}
	printf("\n");
	*/

	LIST_DESTRUCTOR(&testList);
	free(testArray);
	return 0;
}

int CompareFunc(const void *front, const void *rear)
{
	if (strcmp(((NODE *)front)->name, ((NODE *)rear)->name) > 0){
		//Swap
		return 1;
	}
	//Don't Swap
	return 0;
}

int UnitTest_ShellSort(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);
	NODE *testArray_For_qsort = NULL;
	NODE *temp = NULL;

	for (int i=0 ; i<100 ; i++){
		testList.AddRandom(&testList);
	}

	testList.CopyRawArray(&testList, &testArray_For_qsort);

	if (&testList != testList.Sort(&testList)){
		PRINTF_ERROR("ERROR: Sort Fail.\n");
		return -1;
	}

	qsort(testArray_For_qsort, testList.size, sizeof(NODE), &CompareFunc);
	testList.Sort(&testList);

	temp = testList.begin;
	for (int i=0 ; i<testList.size ; i++){
		if (strcmp(temp->name, testArray_For_qsort[i].name) != 0){
			return (-1)*(i);
		}
		temp = temp->next;
	}

	LIST_DESTRUCTOR(&testList);
	free(testArray_For_qsort);

	return 0;
}

int UnitTest(void)
{
	int err = 0;
	err = UnitTest_List();
	printf(COLOR_BLACK "Unit Test for Creating Random Linked List: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK);
		printf(COLOR_BLACK "Error Code: "
				COLOR_RED "%d\n"
				COLOR_BLACK, err);
		return -1;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK);

	err = UnitTest_ShellSort();
	printf(COLOR_BLACK "Unit Test for Shell Sort toward Linked List: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "FAIL\n" COLOR_BLACK);
		printf(COLOR_BLACK "Error Code: "
				COLOR_RED "%d\n"
				COLOR_BLACK, err);
		return -2;
	}
	printf(COLOR_GREEN "SUCCESS\n" COLOR_BLACK);

	return 0;
}
