#include "test.h"
#include "search.h"

#define SIZE 100000

//Function Definitions
int UnitTest_RandomArray(void)
{
	NODE *testArray = NULL;
	testArray = (NODE *)malloc(sizeof(NODE)*500);

	RandomFill(testArray, 500);
	
	/*
	for (int i=0 ; i<500 ; i++){
		printf("Name: %s, Number: %d\n", testArray[i].name, testArray[i].number);
	}
	*/

	free(testArray);
	return 0;
}

int UnitTest_LinearSearch(void)
{
	NODE *testArray = NULL;
	int index = 0;
	int searchResult = 0;

	testArray = (NODE *)malloc(sizeof(NODE)*SIZE);

	RandomFill(testArray, SIZE);

	srand((unsigned int)time(NULL));
	index = rand()%(SIZE);

	strncpy(testArray[index].name, "lcvd1111", STRING_LEN);
	testArray[index].number = 123456;

	searchResult = LinearSearch(testArray, SIZE, "lcvd1111");

	if (searchResult != index){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (strcmp(testArray[searchResult].name, "lcvd1111")){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (testArray[searchResult].number != 123456){
		UNIT_TEST_FAIL;
		return -3;
	}

	/*
	printf("Array[%d]: name is %s, number is %d\n"
			, searchResult
			, testArray[searchResult].name
			, testArray[searchResult].number);
	*/

	free(testArray);

	return 0;
}
