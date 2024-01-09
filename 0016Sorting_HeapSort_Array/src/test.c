#include "test.h"

int UnitTest_Heap(void)
{
	return 0;
}

int UnitTest_Array(void)
{
	return 0;
}

int UnitTest_HeapSort(void)
{
	return 0;
}

int UnitTest(void)
{
	int err = 0;

	err = UnitTest_Heap();
	printf(COLOR_BLACK "Unit Test for Priority Queue using Heap: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "FAIL.\n" COLOR_BLACK );
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d\n" COLOR_BLACK, err);
	}
	printf(COLOR_GREEN "SUCCESS.\n" COLOR_BLACK);

	err = UnitTest_Array();
	printf(COLOR_BLACK "Unit Test for Creating Random Array: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "FAIL.\n" COLOR_BLACK );
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d\n" COLOR_BLACK, err);
	}
	printf(COLOR_GREEN "SUCCESS.\n" COLOR_BLACK);

	err = UnitTest_HeapSort();
	printf(COLOR_BLACK "Unit Test for Heap Sort on Array: " COLOR_BLACK);
	if (err){
		printf(COLOR_RED "FAIL.\n" COLOR_BLACK );
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d\n" COLOR_BLACK, err);
	}
	printf(COLOR_GREEN "SUCCESS.\n" COLOR_BLACK);

	return 0;
}
