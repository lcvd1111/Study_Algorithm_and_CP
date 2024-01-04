#include "test.hh"
#include "search.hh"

int UnitTest_RandomArray(void)
{
	std::string testStr("lcvd_1111");
	ARRAY testArray;
	testArray.AddRandom(1000);
	//testArray.Print();

	testArray.Sort();
	//testArray.Print();

	testArray.ChangeRandomElement(testStr, 777);
	//testArray.Print();

	testArray.Sort();
	//testArray.Print();

	return 0;
}

int UnitTest_LinearSearch(void)
{
	std::string testStr("lcvd_1111");
	ARRAY testArray;
	testArray.AddRandom(1002000);
	testArray.ChangeRandomElement(testStr, 777);
	NODE &searchOut = testArray.LinearSearch(testStr);
	if (strcmp(searchOut.name.c_str(), "SEARCH_FAIL") == 0){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (strcmp(searchOut.name.c_str(), "lcvd_1111") != 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchOut.number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}

	testStr = "T_E_S_T";
	NODE &searchOut2 = testArray.LinearSearch(testStr);
	if (strcmp(searchOut2.name.c_str(), "SEARCH_FAIL") != 0){
		UNIT_TEST_FAIL;
		return -4;
	}

	return 0;
}

int UnitTest_JumpSearch(void)
{
	std::string testStr("lcvd_1111");
	ARRAY testArray;
	testArray.AddRandom(4004000);
	testArray.ChangeRandomElement(testStr, 777);
	
	if (FindSqrt(testArray.Size()) != 2000){
		UNIT_TEST_FAIL;
		return -1;
	}

	testArray.Sort();

	NODE &searchOut = testArray.JumpSearch(testStr);
	if (strcmp(searchOut.name.c_str(), "SEARCH_FAIL") == 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (strcmp(searchOut.name.c_str(), "lcvd_1111") != 0){
		UNIT_TEST_FAIL;
		return -3;
	}

	if (searchOut.number != 777){
		UNIT_TEST_FAIL;
		return -4;
	}

	testStr = "T_E_S_T";
	NODE &searchOut2 = testArray.JumpSearch(testStr);
	if (strcmp(searchOut2.name.c_str(), "SEARCH_FAIL") != 0){
		UNIT_TEST_FAIL;
		return -5;
	}

	return 0;
}

int UnitTest_BinarySearch(void)
{
	std::string testStr("lcvd_1111");
	ARRAY testArray;
	testArray.AddRandom(4004000);
	testArray.ChangeRandomElement(testStr, 777);
	testArray.Sort();

	NODE &searchOut = testArray.BinarySearch(testStr);
	if (strcmp(searchOut.name.c_str(), "SEARCH_FAIL") == 0){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (strcmp(searchOut.name.c_str(), "lcvd_1111") != 0){
		UNIT_TEST_FAIL;
		return -2;
	}

	if (searchOut.number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}

	testStr = "T_E_S_T";
	NODE &searchOut2 = testArray.BinarySearch(testStr);
	if (strcmp(searchOut2.name.c_str(), "SEARCH_FAIL") != 0){
		UNIT_TEST_FAIL;
		return -4;
	}


	return 0;
}

int UnitTest_TimeMeasurement(void)
{
	std::chrono::high_resolution_clock::time_point beginTime;
	std::chrono::high_resolution_clock::time_point endTime;
	std::chrono::duration<double> durationTime;

	std::string testStr("lcvd_1111");
	ARRAY testArray;
	testArray.AddRandom(4004000);
	testArray.ChangeRandomElement(testStr, 777);

	beginTime = std::chrono::high_resolution_clock::now();
	NODE &searchOut1 = testArray.LinearSearch(testStr);
	endTime = std::chrono::high_resolution_clock::now();
	if (searchOut1.number != 777){
		UNIT_TEST_FAIL;
		return -1;
	}
	durationTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - beginTime);
	std::cout << "[Linear Search]: " << durationTime.count() << std::endl;

	testArray.Sort();
	beginTime = std::chrono::high_resolution_clock::now();
	NODE &searchOut2 = testArray.JumpSearch(testStr);
	endTime = std::chrono::high_resolution_clock::now();
	if (searchOut2.number != 777){
		UNIT_TEST_FAIL;
		return -2;
	}
	durationTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - beginTime);
	std::cout << "[Jump Search]:   " << durationTime.count() << std::endl;

	beginTime = std::chrono::high_resolution_clock::now();
	NODE &searchOut3 = testArray.BinarySearch(testStr);
	endTime = std::chrono::high_resolution_clock::now();
	if (searchOut3.number != 777){
		UNIT_TEST_FAIL;
		return -3;
	}
	durationTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - beginTime);
	std::cout << std::fixed << "[Binary Search]: " << durationTime.count() << std::endl;


	std::cout << std::endl; 

	return 0;
}
