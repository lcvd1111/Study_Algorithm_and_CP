#include "test.h"
#define TEST_SIZE 1000

static int CompareFunc(const void *prev, const void *rear)
{
	return (((LIST_NODE *)prev)->number - ((LIST_NODE *)rear)->number);
}

int UnitTest(void)
{
	LIST testList;
	LIST_METHOD_CONSTRUCTOR(&testList);
	LIST_NODE testArray[TEST_SIZE];
	LIST_NODE *tempNode = NULL;

	testList.Method->Add_Random(&testList, TEST_SIZE);
	testList.Method->Copy_to_Array(&testList, testArray);
	//testList.Method->Print(&testList);

	testList.Method->Sort(&testList);
	//testList.Method->Print(&testList);
	qsort(testArray, TEST_SIZE, sizeof(LIST_NODE), &CompareFunc);

	tempNode = testList.begin;
	for (int i=0 ; i<TEST_SIZE ; i++){
		if (testArray[i].number != tempNode->number){
			return -1-i;
		}
		tempNode = tempNode->next;
	}

	LIST_METHOD_DESTRUCTOR(&testList);
	return 0;
}
