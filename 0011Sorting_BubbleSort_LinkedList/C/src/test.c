#include "test.h"
#include "list.h"

int UnitTest_RandomList(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);
	testList.AddRandom(&testList, 10);
	//testList.Print(&testList);

	testList.ChangeRandomElement(&testList, "lcvd1111", 777);
	//testList.Print(&testList);

	testList.Swap(&testList, testList.begin, testList.begin->next);
	testList.Swap(&testList, testList.begin->next, testList.begin->next->next);
	testList.Swap(&testList, testList.end->prev, testList.end);
	//testList.Print(&testList);

	LIST_DESTRUCTOR(&testList);

	return 0;
}

int CompareFunc(const void *front, const void *rear)
{
	if (strcmp(((NODE *)front)->name, ((NODE *)rear)->name) > 0){
		return 1;
	}
	return 0;
}

int UnitTest_BubbleSort(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);
	NODE testArray[5000];
	NODE *temp = NULL;

	testList.AddRandom(&testList, 5000);

	temp = testList.begin;
	for (int i=0 ; i<testList.size ; i++){
		memcpy(testArray[i].name, temp->name, sizeof(char)*NAME_LEN);
		temp = temp->next;
	}

	testList.Sort(&testList);
	qsort(testArray, 5000, sizeof(NODE), &CompareFunc);

	//testList.Print(&testList);

	temp = testList.begin;
	for (int i=0 ; i<testList.size ; i++){
		if (strcmp(temp->name, testArray[i].name) != 0){
			UNIT_TEST_FAIL;
			return -1;
		}
		temp = temp->next;
	}

	LIST_DESTRUCTOR(&testList);
	return 0;
}

int UnitTest(void)
{
	int err = 0;

	err = UnitTest_RandomList();
	if (err){
		printf(COLOR_BLACK "Unit Test for Creating Random List: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for Creating Random List: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	err = UnitTest_BubbleSort();
	if (err){
		printf(COLOR_BLACK "Unit Test for Bubble Sort: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -2;
	}
	printf(COLOR_BLACK "Unit Test for Bubble Sort: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	return 0;
}
