#include "test.h"
#define TEST_SIZE 1000

int UnitTest_List(void)
{
	LIST testList;
	LIST_METHOD_CONSTRUCTOR(&testList);

	testList.Add_Random(&testList, 100);
	//testList.Print(&testList);

	LIST_METHOD_DESTRUCTOR(&testList);

	return 0;
}

int CustomCompare(const void *prev, const void *rear)
{
	return (strcmp(((LIST_NODE *)prev)->name, ((LIST_NODE *)rear)->name));
}

int UnitTest_Sort(void)
{
	LIST testList;
	LIST_METHOD_CONSTRUCTOR(&testList);
	LIST_NODE *testArray = (LIST_NODE *)malloc(sizeof(LIST_NODE)*TEST_SIZE);
	LIST_NODE *temp = NULL;

	testList.Add_Random(&testList, TEST_SIZE);
	testList.Copy_to_Array(&testList, testArray);

	testList.Sort(&testList);
	qsort(testArray, TEST_SIZE, sizeof(LIST_NODE), &CustomCompare);

	temp = testList.begin;

	for (int i=0 ; i<TEST_SIZE ; i++){
		if (strcmp(testArray[i].name, temp->name)){
			PRINTF_ERROR("UNIT TEST FAILED.\n");
			return -1;
		}
		temp = temp->next;
	}

	LIST_METHOD_DESTRUCTOR(&testList);

	free(testArray);

	return 0;
}

int UnitTest(void)
{
	if (UnitTest_List()){
		printf(COLOR_BLACK "Unit Test for List: " COLOR_RED "FAIL\n" COLOR_BLACK);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for List: " COLOR_GREEN "SUCCESS\n" COLOR_BLACK);

	if (UnitTest_Sort()){
		printf(COLOR_BLACK "Unit Test for Merge Sort on list: " COLOR_RED "FAIL\n" COLOR_BLACK);
		return -2;
	}
	printf(COLOR_BLACK "Unit Test for Merge Sort on list: " COLOR_GREEN "SUCCESS\n" COLOR_BLACK);
	
	return 0;
}

