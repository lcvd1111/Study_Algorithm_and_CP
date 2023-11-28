#include "test.hh"
#include "search.hh"

int UnitTest_RandomVector(void)
{
	VECTOR testVector;

	for (int i=0 ; i<50000 ; i++){
		testVector.Add();
	}

	//testVector.Print();

	return 0;
}

int UnitTest_LinearSearch(void)
{
	VECTOR testVector;
	std::string temp;
	NODE searchOutput;

	for (int i=0 ; i<1000000 ; i++){
		testVector.Add();
	}

	temp = "lcvb1111";
	testVector.Add(temp, 12345);

	//testVector.Print();

	searchOutput = testVector.Search(temp);
	//std::cout << "Name: " << searchOutput.name << ", Number: " << searchOutput.number << std::endl;
	if (searchOutput.name != temp){
		UNIT_TEST_FAIL;
		return -1;
	}

	if (searchOutput.number != 12345){
		UNIT_TEST_FAIL;
		return -2;
	}

	return 0;
}

