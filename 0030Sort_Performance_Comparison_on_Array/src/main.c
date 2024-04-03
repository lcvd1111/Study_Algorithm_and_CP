#include "test.h"
#define UNIT_TEST_ON

int main(void)
{
#ifdef UNIT_TEST_ON
	if (UnitTest()){
		return -1;
	}
#endif

	if(Sort_Comparison()){
		return -2;
	}

	return 0;
}
