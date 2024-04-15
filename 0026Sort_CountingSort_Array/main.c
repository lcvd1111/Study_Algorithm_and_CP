#include "test.h"
int main(void)
{
	int err = 0;
	if(err = UnitTest()){
		printf(COLOR_RED "Unit Test Fail.\n");
		printf("Error Code: %d\n" COLOR_BLACK, err);
	}
	printf(COLOR_GREEN "Unit Test Success.\n" COLOR_BLACK);
	return 0;
}
