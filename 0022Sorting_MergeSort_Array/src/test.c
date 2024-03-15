#include "test.h"
#define TEST_SIZE 1000

int UnitTest_Array(void)
{
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, 100);
	testArray.Fill_Random(&testArray);
	//testArray.Print(&testArray);
	ARRAY_METHOD_DESTRUCTOR(&testArray);
	return 0;
}

int CustomCompare(const void *prev, const void *rear)
{
	int cmpResult = strcmp(((NODE *)prev)->name, ((NODE *)rear)->name);
	return cmpResult;
}

int UnitTest_Sort(void)
{
	NODE rawArray[TEST_SIZE];
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, TEST_SIZE);

	testArray.Fill_Random(&testArray);
	testArray.Copy_to_Raw_Array(&testArray, rawArray);

	testArray.Sort(&testArray);
	qsort(rawArray, TEST_SIZE, sizeof(NODE), CustomCompare);

	for (int i=0 ; i<TEST_SIZE ; i++){
		if (strcmp(rawArray[i].name, (testArray.nodeArray)[i].name))
			return (-1)*(i);
	}

	ARRAY_METHOD_DESTRUCTOR(&testArray);
	return 0;
}

int UnitTest_Stack(void)
{
	STACK testStack;
	STACK_METHOD_CONSTRUCTOR(&testStack);

	STACK_NODE testNode;
	STACK_NODE outputNode;

	if (testStack.Size(&testStack) != 0){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (testStack.Pop(&testStack, &outputNode) != NULL){
		UNIT_TEST_FAIL;
		return -2;
	}

	testNode.begin_Index = 0;
	testNode.end_Index = 0;
	testNode.status = 0;

	testStack.Push(&testStack, &testNode);

	testNode.begin_Index = 1;
	testNode.end_Index = 1;
	testNode.status = 1;

	testStack.Push(&testStack, &testNode);

	testNode.begin_Index = 2;
	testNode.end_Index = 2;
	testNode.status = 2;

	testStack.Push(&testStack, &testNode);

	testNode.begin_Index = 3;
	testNode.end_Index = 3;
	testNode.status = 3;

	testStack.Push(&testStack, &testNode);

	if (testStack.Pop(&testStack, &outputNode) != &testStack){
		UNIT_TEST_FAIL;
		return -3;
	}

	assert(outputNode.begin_Index == 3 && outputNode.end_Index == 3);
	assert(outputNode.status == 3);

	if (testStack.Pop(&testStack, &outputNode) != &testStack){
		UNIT_TEST_FAIL;
		return -4;
	}

	assert(outputNode.begin_Index == 2 && outputNode.end_Index == 2);
	assert(outputNode.status == 2);

	if (testStack.Pop(&testStack, &outputNode) != &testStack){
		UNIT_TEST_FAIL;
		return -5;
	}

	assert(outputNode.begin_Index == 1 && outputNode.end_Index == 1);
	assert(outputNode.status == 1);

	if (testStack.Pop(&testStack, &outputNode) != &testStack){
		UNIT_TEST_FAIL;
		return -6;
	}

	assert(outputNode.begin_Index == 0 && outputNode.end_Index == 0);
	assert(outputNode.status == 0);

	if (testStack.Pop(&testStack, &outputNode) != NULL){
		UNIT_TEST_FAIL;
		return -7;
	}

	assert(outputNode.begin_Index == 0 && outputNode.end_Index == 0);
	assert(outputNode.status == 0);
	STACK_METHOD_DESTRUCTOR(&testStack);

	return 0;
}

int UnitTest_Sort_Iterative(void)
{
	NODE rawArray[TEST_SIZE];
	ARRAY testArray;
	ARRAY_METHOD_CONSTRUCTOR(&testArray, TEST_SIZE);

	testArray.Fill_Random(&testArray);
	testArray.Copy_to_Raw_Array(&testArray, rawArray);

	testArray.Sort2(&testArray);
	qsort(rawArray, TEST_SIZE, sizeof(NODE), CustomCompare);

	for (int i=0 ; i<TEST_SIZE ; i++){
		if (strcmp(rawArray[i].name, (testArray.nodeArray)[i].name))
			return (-1)*(i);
	}

	ARRAY_METHOD_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest(void)
{
	if (UnitTest_Array()){
		printf(COLOR_BLACK "Unit Test for Array: " COLOR_RED "FAIL\n" COLOR_BLACK);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for Array: " COLOR_GREEN "SUCCESS\n" COLOR_BLACK);

	if (UnitTest_Sort()){
		printf(COLOR_BLACK "Unit Test for Merge Sort on array: " COLOR_RED "FAIL\n" COLOR_BLACK);
		return -2;
	}
	printf(COLOR_BLACK "Unit Test for Merge Sort on array: " COLOR_GREEN "SUCCESS\n" COLOR_BLACK);
	
	if (UnitTest_Stack()){
		printf(COLOR_BLACK "Unit Test for Stack: " COLOR_RED "FAIL\n" COLOR_BLACK);
		return -3;
	}
	printf(COLOR_BLACK "Unit Test for Stack: " COLOR_GREEN "SUCCESS\n" COLOR_BLACK);

	if (UnitTest_Sort_Iterative()){
		printf(COLOR_BLACK "Unit Test for Merge Sort on array using iterative implementation: " COLOR_RED "FAIL\n" COLOR_BLACK);
		return -3;
	}
	printf(COLOR_BLACK "Unit Test for Merge Sort on array using iterative implementation: " COLOR_GREEN "SUCCESS\n" COLOR_BLACK);



	return 0;
}

