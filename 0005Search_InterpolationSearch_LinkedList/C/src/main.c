#include "test.h"

int main(int argc, char **argv)
{
	int err = 0;
	err = UnitTest_RandomList();
	if (err){
		printf(COLOR_BLACK "Unit Test for Creating Random List: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for Creating Random List: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	err = UnitTest_InterpolationSearch();
	if (err){
		printf(COLOR_BLACK "Unit Test for Interpolation Search toward Linked List: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -2;
	}
	printf(COLOR_BLACK "Unit Test for Interpolation Search toward Linked List: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	return 0;
}
