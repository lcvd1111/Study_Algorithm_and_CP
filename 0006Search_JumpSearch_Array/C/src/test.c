#include "test.h"
#include "search.h"

int UnitTest_RandomArray(void)
{
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 300);

	testArray.FillRandom(&testArray);
	//testArray.Print(&testArray);

	testArray.Sort(&testArray);
	//testArray.Print(&testArray);

	testArray.ChangeRandomElement(&testArray, "lcvd_1111", 777);
	//testArray.Print(&testArray);

	testArray.Sort(&testArray);
	//testArray.Print(&testArray);

	ARRAY_DESTRUCTOR(&testArray);
	return 0;
}

int UnitTest_JumpSearch(void)
{
	return 0;
}
