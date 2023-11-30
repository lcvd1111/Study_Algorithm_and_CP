#include "test.hh"

int main(int argc, char **argv)
{
	int err = 0;
	err = UnitTest_RandomArray();
	if (err){
		std::cout << "Unit test for creating random array: " COLOR_RED "FAIL. " << COLOR_BLACK << std::endl;
		std::cout << "Error code: " COLOR_RED << err << COLOR_BLACK << std::endl;
		return -1;
	}
	std::cout << "Unit test for creating random array: " COLOR_GREEN "SUCCESS. " << COLOR_BLACK << std::endl;

	err = UnitTest_BinarySearch();
	if (err){
		std::cout << "Unit test for binary search toward array: " COLOR_RED "FAIL. " << COLOR_BLACK << std::endl;
		std::cout << "Error code: " COLOR_RED << err << COLOR_BLACK << std::endl;
		return -2;
	}
	std::cout << "Unit test for binary search toward array: " COLOR_GREEN "SUCCESS. " << COLOR_BLACK << std::endl;

	return 0;
}
