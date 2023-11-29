#include "test.hh"

int main(int argc, char **argv)
{
	int err = 0;
	err = UnitTest_RandomList();
	if (err){
		std::cout << "Unit Test for Creating Random List: " << COLOR_RED "FAIL" COLOR_BLACK << std::endl;
		std::cout << "Error Code: " << COLOR_RED << err << COLOR_BLACK << std::endl;
		return -1;
	}
	std::cout << "Unit Test for Creating Random List: " << COLOR_GREEN "SUCCESS" COLOR_BLACK << std::endl;

	err = UnitTest_LinearSearch();
	if (err){
		std::cout << "Unit Test for Linear Search Toward Linked List: " << COLOR_RED "FAIL" COLOR_BLACK << std::endl;
		std::cout << "Error Code: " << COLOR_RED << err << COLOR_BLACK << std::endl;
		return -2;
	}
	std::cout << "Unit Test for Creating Random List: " << COLOR_GREEN "SUCCESS" COLOR_BLACK << std::endl;

	return 0;
}
