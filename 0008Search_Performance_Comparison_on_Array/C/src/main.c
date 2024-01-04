#include "test.h"

int main(int argc, char **argv)
{
	int err = 0;
	/*
	err = UnitTest_RandomArray();
	if (err){
		printf(COLOR_BLACK "Unit Test for Creating the random array: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for Creating the random array: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	err = UnitTest_LinearSearch();
	if (err){
		printf(COLOR_BLACK "Unit Test for Linear search toward the array: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for Linear search toward the array: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	err = UnitTest_JumpSearch();
	if (err){
		printf(COLOR_BLACK "Unit Test for Jump search toward the array: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for Jump search toward the array: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	err = UnitTest_BinarySearch();
	if (err){
		printf(COLOR_BLACK "Unit Test for Binary search toward the array: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -1;
	}
	printf(COLOR_BLACK "Unit Test for Binary search toward the array: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");
	*/

	err = UnitTest_TimeMeasurement();
	if (err){
		printf(COLOR_BLACK "Unit Test for Time Measurement: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf(COLOR_BLACK "Error code: " COLOR_RED "%d" COLOR_BLACK "\n", err);
		return -1;
	}

	return 0;
}
