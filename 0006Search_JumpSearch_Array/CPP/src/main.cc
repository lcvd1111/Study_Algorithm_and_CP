#include "test.hh"

int main(int argc, char **argv)
{
	int err = 0;
	err = UnitTest_RandomArray();
	if (err){
		std::cout << COLOR_BLACK "Unit Test for Creating Random Array: " COLOR_RED "FAIL" COLOR_BLACK << std::endl;
		std::cout << COLOR_BLACK "Error Code: " << COLOR_RED << err << COLOR_BLACK << std::endl;
		return -1;
	}
	std::cout << COLOR_BLACK "Unit Test for Creating Random Array: " COLOR_GREEN "SUCCESS" COLOR_BLACK << std::endl;

	err = UnitTest_Search();
	if (err){
		std::cout << COLOR_BLACK "Unit Test for Jump Search toward Array: " COLOR_RED "FAIL" COLOR_BLACK << std::endl;
		std::cout << COLOR_BLACK "Error Code: " << COLOR_RED << err << COLOR_BLACK << std::endl;
		return -2;
	}
	std::cout << COLOR_BLACK "Unit Test for Jump Search toward Array: " COLOR_GREEN "SUCCESS" COLOR_BLACK << std::endl;

	return 0;
}
