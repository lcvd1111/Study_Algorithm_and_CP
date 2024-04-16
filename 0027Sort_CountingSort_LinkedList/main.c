#include "test.h"

int main(void)
{
	int err = 0;
	if (err = UnitTest())
	{
		printf(COLOR_RED "Unit test Failed!\n" COLOR_BLACK);
		printf(COLOR_RED "Error Code: %d\n" COLOR_BLACK, err);
		return -1;
	}
	printf(COLOR_GREEN "Unit test Success!\n" COLOR_BLACK);

	return 0;
}
