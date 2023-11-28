#include "test.h"

int main(int argc, char **argv)
{
	int err = 0;
	err = UnitTest_RandomArray();
	if (err){
		printf(COLOR_RED "Unit Test for Random Array Generation: FAIL.\n");
		printf("ERROR CODE: %d\n", err);
		return -1;
	}
	printf(COLOR_GREEN "Unit Test for Random Array Generation: SUCCESS.\n");

	err = UnitTest_LinearSearch();
	if (err){
		printf(COLOR_RED "Unit Test for Linear Search: FAIL.\n");
		printf("ERROR CODE: %d\n", err);
		return -2;
	}
	printf(COLOR_GREEN "Unit Test for Linear Search: SUCCESS.\n");

	return 0;
}
