#include "test.h"

int main(int argc, char **argv)
{
	int err = 0;
	err = UnitTest_RandomArray();
	if (err){
		printf(COLOR_BLACK "Unit Test for Creating random array: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for Creating random array: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	err = UnitTest_JumpSearch();
	if (err){
		printf(COLOR_BLACK "Unit Test for jump search toward array: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error Code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -2;
	}
	printf(COLOR_BLACK "Unit Test for jump search toward array: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	return 0;
}
