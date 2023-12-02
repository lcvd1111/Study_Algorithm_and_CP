#include "test.h"

int main(int argc, char **argv)
{
	int err = 0;
	err = UnitTest_RandomArray();
	if (err){
		printf("Unit test for Creating Random Array: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf("Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -1;
	}
		printf("Unit test for Creating Random Array: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	err = UnitTest_InterpolationSearch();
	if (err){
		printf("Unit test for Interpolation Search toward array: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf("Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -2;
	}
		printf("Unit test for Interpolation Search toward array: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	return 0;
}
