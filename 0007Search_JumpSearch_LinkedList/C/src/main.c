#include "test.h"

int main(int argc, char **argv)
{
	int err = 0;
	err = UnitTest_RandomList();
	if (err){
		printf(COLOR_BLACK "Unit Test for Creating the random list: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for Creating the random list: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	err = UnitTest_JumpSearch();
	if (err){
		printf(COLOR_BLACK "Unit Test for Jump Search toward the random list: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -2;
	}
	printf(COLOR_BLACK "Unit Test for Jump Search toward the random list: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	return 0;
}
