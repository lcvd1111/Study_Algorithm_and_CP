#include "test.h"
#define TEST_SIZE 5000

static int CompareFunc(const void *prev, const void *rear)
{
	return (((NODE *)prev)->number - ((NODE *)rear)->number);
}

int UnitTest(void)
{
	ARRAY testArray;
	NODE testRawArray[TEST_SIZE];

	ARRAY_METHOD_CONSTRUCTOR(&testArray, TEST_SIZE);

	testArray.Method->Fill_Random(&testArray);
	testArray.Method->Copy_to_Raw_Array(&testArray, testRawArray);

	//testArray.Method->Print(&testArray);
	testArray.Method->Sort(&testArray);
	qsort(testRawArray, TEST_SIZE, sizeof(NODE), &CompareFunc);
	//testArray.Method->Print(&testArray);

	for (int i=0 ; i<TEST_SIZE ; i++){
		if (testRawArray[i].number != (testArray.nodeArray)[i].number){
			return -1-i;
		}
	}

	ARRAY_METHOD_DESTRUCTOR(&testArray);
	return 0;
}
