#include "test.hh"

int main(int argc, char **argv)
{
	int err = 0;

	err = UnitTest_RandomVector();
	if (err){
		std::cout << COLOR_RED << "Unit Test for creating random vector: FAIL." << std::endl;
		std::cout << "Error code: " << err << std::endl;
		return -1;
	}
	std::cout << COLOR_GREEN << "Unit Test for creating random vector: SUCCESS." << std::endl << COLOR_BLACK;

	err = UnitTest_LinearSearch();
	if (err){
		std::cout << COLOR_RED << "Unit Test for creating random vector: FAIL." << std::endl;
		std::cout << "Error code: " << err << std::endl;
		return -2;
	}
	std::cout << COLOR_GREEN << "Unit Test for creating linear search: SUCCESS." << std::endl << COLOR_BLACK;

	return 0;
}
