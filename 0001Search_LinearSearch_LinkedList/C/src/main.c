#include "test.h"

int main(int argc, char **argv)
{
	int err = 0;

	err = UnitTest_RandomList();
	if (err){
		printf(COLOR_RED "Unit Test for creating random list: FAIL.\n" );
		printf("Error code: %d\n" COLOR_BLACK, err);
		return -1;
	}
	printf(COLOR_GREEN "Unit Test for creating random list: SUCCESS.\n" COLOR_BLACK);

	err = UnitTest_Search();
	if (err){
		printf(COLOR_RED "Unit Test for Search: FAIL.\n" );
		printf("Error code: %d\n" COLOR_BLACK, err);
		return -2;
	}
	printf(COLOR_GREEN "Unit Test for Linear Search toward linked list: SUCCESS.\n" COLOR_BLACK);

	return 0;
}
