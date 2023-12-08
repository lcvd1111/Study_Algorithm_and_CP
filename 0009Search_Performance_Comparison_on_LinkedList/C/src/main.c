#include "test.h"

int main(int argc, char **argv)
{
	int err = 0;
	/*
	err = UnitTest_RandomList();
	if (err){
		printf(COLOR_BLACK "Unit Test for Creating the random list: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for Creating the random list: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	err = UnitTest_LinearSearch();
	if (err){
		printf(COLOR_BLACK "Unit Test for Linear Search toward list: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -2;
	}
	printf(COLOR_BLACK "Unit Test for Linear Search toward list: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	err = UnitTest_JumpSearch();
	if (err){
		printf(COLOR_BLACK "Unit Test for Jump Search toward list: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -3;
	}
	printf(COLOR_BLACK "Unit Test for Jump Search toward list: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	err = UnitTest_BinarySearch();
	if (err){
		printf(COLOR_BLACK "Unit Test for Binary Search toward list: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -4;
	}
	printf(COLOR_BLACK "Unit Test for Binary Search toward  list: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");
	*/

	err = UnitTest_TimeMeasure();
	if (err){
		printf(COLOR_BLACK "Unit Test for time duration comparison between several searching algorithm toward list: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -5;
	}
	printf("\n");

	return 0;
}
