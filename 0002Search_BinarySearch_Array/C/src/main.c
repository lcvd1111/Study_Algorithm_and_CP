#include "test.h"

int main(int argc, char **argv)
{
	int err = 0;
	err = UnitTest_RandomArray();
	if (err){
		printf(COLOR_BLACK "Unit Test for Creating random array: " COLOR_RED "FAIL\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d\n", err);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for Creating random array: " COLOR_GREEN "SUCCESS\n");

	err = UnitTest_BinarySearch();
	if (err){
		printf(COLOR_BLACK "Unit Test for binary search toward array: " COLOR_RED "FAIL\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d\n", err);
		return -2;
	}
	printf(COLOR_BLACK "Unit Test for binary search toward array: " COLOR_GREEN "SUCCESS\n");

	return 0;
}
