#include "test.h"

int UnitTest_List(void)
{
	return 0;
}

int UnitTest_ShellSort(void)
{
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
