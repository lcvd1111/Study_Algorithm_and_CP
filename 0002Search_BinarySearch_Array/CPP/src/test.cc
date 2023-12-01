#include "test.hh"
#include "search.hh"

int UnitTest_RandomArray(void)
{
	std::string testString = "lcvd1111";
	ARRAY testArray;
	
	testArray.AddRandom(10);

	//testArray.Print();
	//std::cout << std::endl;

	testArray.Sort();

	//testArray.Print();
	//std::cout << std::endl;

	testArray.ChangeRandomElement(testString, 77777);

	//testArray.Print();
	//std::cout << std::endl;
	
	testArray.Sort();

	//testArray.Print();
	return 0;
}

int UnitTest_BinarySearch(void)
{
	ARRAY testArray;
	std::string tempString = "lcvd1111";

	testArray.AddRandom(1000);
	testArray.ChangeRandomElement(tempString, 777);
	testArray.Sort();
	
	if (testArray.BinarySearch(tempString).name != tempString){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (testArray.BinarySearch(tempString).number != 777){
		UNIT_TEST_FAIL;
		return -2;
	}

	tempString = "T_E_S_T"; //NODE.name can't contain underbar.
	if (testArray.BinarySearch(tempString).name != std::string("SEARCH_FAIL")){
		UNIT_TEST_FAIL;
		return -3;
	}

	return 0;
}
