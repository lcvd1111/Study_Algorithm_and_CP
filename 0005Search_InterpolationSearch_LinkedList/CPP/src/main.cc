#include "test.hh"

int main(int argc, char **argv)
{
	int err = 0;
	err = UnitTest_RandomList();
	if (err){
		std::cout << COLOR_BLACK "Unit test for Creating Random List: " COLOR_RED "FAIL" COLOR_BLACK  << std::endl;
		std::cout << COLOR_BLACK "Error Code: " COLOR_RED << err << COLOR_BLACK << std::endl;
	}
	std::cout << COLOR_BLACK "Unit test for Creating Random List: " COLOR_GREEN "SUCCESS" COLOR_BLACK  << std::endl;

	err = UnitTest_InterpolationSearch();
	if (err){
		std::cout << COLOR_BLACK "Unit test for Interpolation Search toward linked list: " COLOR_RED "FAIL" COLOR_BLACK  << std::endl;
		std::cout << COLOR_BLACK "Error Code: " COLOR_RED << err << COLOR_BLACK << std::endl;
	}
	std::cout << COLOR_BLACK "Unit test for Interpolation Search toward linked list: " COLOR_GREEN "SUCCESS" COLOR_BLACK  << std::endl;

	return 0;
}
