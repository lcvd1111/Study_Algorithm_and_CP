#include "test.h"
#include "search.h"

int UnitTest_RandomList(void)
{
	LIST testList;
	LIST_CONSTRUCTOR(&testList);

	for (int i=0 ; i<100 ; i++){
		testList.AddRandom(&testList);
	}
	//testList.Print(&testList);

	testList.Sort(&testList);
	//testList.Print(&testList);

	testList.ChangeRandomElement(&testList, "lcvd_1111", 777);
	//testList.Print(&testList);

	testList.Sort(&testList);
	//testList.Print(&testList);

	LIST_DESTRUCTOR(&testList);

	return 0;
}

int UnitTest_LinearSearch(void)
{
	NODE *searchResult = NULL;
	LIST testList;
	LIST_CONSTRUCTOR(&testList);

	for (int i=0 ; i<1002000 ; i++){
		testList.AddRandom(&testList);
	}

	testList.ChangeRandomElement(&testList, "lcvd_1111", 777);

	searchResult = testList.LinearSearch(&testList, "lcvd_1111");
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

	searchResult = testList.LinearSearch(&testList, "T_E_S_T");
	if (searchResult != NULL){
		UNIT_TEST_FAIL;
		return -4;
	}

	LIST_DESTRUCTOR(&testList);
	
	return 0;
}

int UnitTest_JumpSearch(void)
{
	NODE *searchResult = NULL;
	LIST testList;
	LIST_CONSTRUCTOR(&testList);

	for (int i=0 ; i<1002000 ; i++){
		testList.AddRandom(&testList);
	}

	testList.ChangeRandomElement(&testList, "lcvd_1111", 777);
	testList.Sort(&testList);

	if (FindSqrt(testList.size) != 1000){
		UNIT_TEST_FAIL;
		return -99;
	}

	searchResult = testList.JumpSearch(&testList, "lcvd_1111");
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

	searchResult = testList.LinearSearch(&testList, "T_E_S_T");
	if (searchResult != NULL){
		UNIT_TEST_FAIL;
		return -4;
	}

	LIST_DESTRUCTOR(&testList);
	
	return 0;
}

int UnitTest_BinarySearch(void)
{
	NODE *searchResult = NULL;
	LIST testList;
	LIST_CONSTRUCTOR(&testList);

	for (int i=0 ; i<3004000 ; i++){
		testList.AddRandom(&testList);
	}

	if (FindSqrt(testList.size) != 3000){
		UNIT_TEST_FAIL;
		return -99;
	}

	testList.ChangeRandomElement(&testList, "lcvd_1111", 777);
	testList.Sort(&testList);

	searchResult = testList.BinarySearch(&testList, "lcvd_1111");
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

	searchResult = testList.LinearSearch(&testList, "T_E_S_T");
	if (searchResult != NULL){
		UNIT_TEST_FAIL;
		return -4;
	}

	LIST_DESTRUCTOR(&testList);
	
	return 0;
}

int UnitTest_TimeMeasure(void)
{
	NODE *searchResult = NULL;
	LIST testList;
	LIST_CONSTRUCTOR(&testList);
	struct timeval time_begin, time_end, time_duration;

	for (int i=0 ; i<1002000 ; i++){
		testList.AddRandom(&testList);
	}

	testList.ChangeRandomElement(&testList, "lcvd_1111", 777);

	//Measuring Linear Search.
	gettimeofday(&time_begin, NULL);
	searchResult = testList.LinearSearch(&testList, "lcvd_1111");
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
	testList.Sort(&testList);

	//Measuring Jump Search.
	gettimeofday(&time_begin, NULL);
	searchResult = testList.JumpSearch(&testList, "lcvd_1111");
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
	searchResult = testList.BinarySearch(&testList, "lcvd_1111");
	if (searchResult->number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}
	gettimeofday(&time_end, NULL);
	timersub(&time_end, &time_begin, &time_duration);
	printf("[Binary Search]: %ld.%06ld\n"
			, (long int)time_duration.tv_sec
			, (long int)time_duration.tv_usec);


	LIST_DESTRUCTOR(&testList);
	
	return 0;
}
