#include "test.h"

int main(int argc, char **argv)
{
	int err = 0;
	err = UnitTest_RandomList();
	if (err){
		printf("Unit Test for Creating Random Linked List: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf("Error Code: %d\n", err);
		return -1;
	}
	printf("Unit Test for Creating Random Linked List: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	err = UnitTest_BinarySearch();
	if (err){
		printf("Unit Test for Binary Search toward Linked List: " COLOR_RED "FAIL" COLOR_BLACK "\n");
		printf("Error Code: %d\n", err);
		return -2;
	}
	printf("Unit Test for Binary Search toward Linked List: " COLOR_GREEN "SUCCESS" COLOR_BLACK "\n");

	return 0;
}
