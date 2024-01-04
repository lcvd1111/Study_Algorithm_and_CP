#include <search.h>

int UnitTest_RandomArray(void)
{
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 100);

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

int UnitTest_LinearSearch(void)
{
	NODE *searchResult = NULL;
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 1002000);
	testArray.FillRandom(&testArray);
	testArray.ChangeRandomElement(&testArray, "lcvd_1111", 777);
	searchResult = testArray.LinearSearch(&testArray, "lcvd_1111");

	if (searchResult == NULL){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (strcmp(searchResult->name, "lcvd_1111") != 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchResult->number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}

	searchResult = testArray.LinearSearch(&testArray, "T_E_S_T");
	if (searchResult != NULL){
		UNIT_TEST_FAIL;
		return -4;
	}

	ARRAY_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest_JumpSearch(void)
{
	NODE *searchResult = NULL;
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 1002000);

	if (FindSqrt(testArray.size) != 1000){
		UNIT_TEST_FAIL;
		return -99;
	}
	
	testArray.FillRandom(&testArray);
	testArray.ChangeRandomElement(&testArray, "lcvd_1111", 777);
	testArray.Sort(&testArray);
	searchResult = testArray.JumpSearch(&testArray, "lcvd_1111");

	if (searchResult == NULL){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (strcmp(searchResult->name, "lcvd_1111") != 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchResult->number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}

	searchResult = testArray.JumpSearch(&testArray, "T_E_S_T");
	if (searchResult != NULL){
		UNIT_TEST_FAIL;
		return -4;
	}

	ARRAY_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest_BinarySearch(void)
{
	NODE *searchResult = NULL;
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 1002000);

	testArray.FillRandom(&testArray);
	testArray.ChangeRandomElement(&testArray, "lcvd_1111", 777);
	testArray.Sort(&testArray);
	searchResult = testArray.BinarySearch(&testArray, "lcvd_1111");

	if (searchResult == NULL){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (strcmp(searchResult->name, "lcvd_1111") != 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchResult->number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}

	searchResult = testArray.BinarySearch(&testArray, "T_E_S_T");
	if (searchResult != NULL){
		UNIT_TEST_FAIL;
		return -4;
	}

	ARRAY_DESTRUCTOR(&testArray);

	return 0;
}

int UnitTest_TimeMeasurement(void)
{
	NODE *searchResult = NULL;
	ARRAY testArray;
	ARRAY_CONSTRUCTOR(&testArray, 9006001);
	struct timeval time_begin, time_end, time_duration;

	testArray.FillRandom(&testArray);

	testArray.ChangeRandomElement(&testArray, "lcvd_1111", 777);

	//Measuring Linear Search.
	gettimeofday(&time_begin, NULL);
	searchResult = testArray.LinearSearch(&testArray, "lcvd_1111");
	if (searchResult->number != 777){
		UNIT_TEST_FAIL;
		return -1;
	}
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	printf("[Linear Search]: %ld.%06ld\n"
			, (long int)time_duration.tv_sec
			, (long int)time_duration.tv_usec);

	//Sorting
	testArray.Sort(&testArray);

	//Measuring Jump Search.
	gettimeofday(&time_begin, NULL);
	searchResult = testArray.JumpSearch(&testArray, "lcvd_1111");
	if (searchResult->number != 777){
		UNIT_TEST_FAIL;
		return -2;
	}
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	printf("[Jump Search]: %ld.%06ld\n"
			, (long int)time_duration.tv_sec
			, (long int)time_duration.tv_usec);

	//Measuring Binary Search.
	gettimeofday(&time_begin, NULL);
	searchResult = testArray.BinarySearch(&testArray, "lcvd_1111");
	if (searchResult->number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	printf("[Binary Search]: %ld.%06ld\n\n"
			, (long int)time_duration.tv_sec
			, (long int)time_duration.tv_usec);


	ARRAY_DESTRUCTOR(&testArray);
	
	return 0;
}
