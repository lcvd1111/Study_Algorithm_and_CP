#include "test.h"

int UnitTest_List(void)
{
	LIST testList;
	LIST_METHOD_CONSTRUCTOR(&testList);

	testList.Add_Random(&testList, 100);
	//testList.Print(&testList);

	LIST_METHOD_DESTRUCTOR(&testList);
	return 0;
}

int UnitTest_BST(void)
{
	BST testBST;
	BST_METHOD_CONSTRUCTOR(&testBST);

	if (testBST.size != 0){
		UNIT_TEST_FAIL;
		return -1;
	}
	testBST.Insert(&testBST, "d", 1);

	if (testBST.size != 1){
		UNIT_TEST_FAIL;
		return -2;
	}

	testBST.Insert(&testBST, "a", 2);

	if (testBST.size != 2){
		UNIT_TEST_FAIL;
		return -3;
	}

	testBST.Insert(&testBST, "c", 3);

	if (testBST.size != 3){
		UNIT_TEST_FAIL;
		return -4;
	}

	testBST.Insert(&testBST, "d", 3);
	
	if (testBST.size != 4){
		UNIT_TEST_FAIL;
		return -5;
	}
	
	testBST.Insert(&testBST, "b", 13);

	BST_METHOD_DESTRUCTOR(&testBST);
	return 0;

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
	LIST_NODE *temp = NULL;
	LIST_NODE testArray[400];

	testList.Add_Random(&testList, 400);
	//testList.Print(&testList);

	testList.Copy_to_Array(&testList, testArray);

	testList.Sort(&testList);
	//testList.Print(&testList);
	qsort(testArray, 400, sizeof(LIST_NODE), &CustomCompare);

	temp = testList.begin;

	for (int i=0 ; i<400 ; i++){
		if (strcmp(testArray[i].name, temp->name)){
			PRINTF_ERROR("UNIT TEST FAILED.\n");
			return -1-i;
		}
		temp = temp->next;
	}

	LIST_METHOD_DESTRUCTOR(&testList);

	return 0;
}

int UnitTest(void)
{
	int errCode = 0;
	
	printf(COLOR_BLACK "Unit Test for List: " COLOR_BLACK);
	if (errCode = UnitTest_List()){
		printf(COLOR_RED "FAIL" COLOR_BLACK);
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -1;
	}
	printf(COLOR_GREEN "SUCCESS.\n" COLOR_BLACK);
	
	printf(COLOR_BLACK "Unit Test for BST: " COLOR_BLACK);
	if (errCode = UnitTest_BST()){
		printf(COLOR_RED "FAIL" COLOR_BLACK);
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -2;
	}
	printf(COLOR_GREEN "SUCCESS.\n" COLOR_BLACK);
	
	printf(COLOR_BLACK "Unit Test for Tree Sort toward Linked List: " COLOR_BLACK);
	if (errCode = UnitTest_Sort()){
		printf(COLOR_RED "FAIL" COLOR_BLACK);
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, errCode);
		return -3;
	}
	printf(COLOR_GREEN "SUCCESS.\n" COLOR_BLACK);

	return 0;
}
