#include "test.hh"

int main(int argc, char **argv)
{
	int err = 0;
	err = UnitTest_RandomList();
	if (err){
		std::cout << COLOR_BLACK "Unit Test for Creating Random List: " COLOR_RED "FAIL" COLOR_BLACK << std::endl;
		std::cout << COLOR_BLACK "Error Code: " << COLOR_RED << err << COLOR_BLACK << std::endl;
		return -1;
	}
	std::cout << COLOR_BLACK "Unit Test for Creating Random List: " COLOR_GREEN "SUCCESS" COLOR_BLACK << std::endl;

	err = UnitTest_LinearSearch();
	if (err){
		std::cout << COLOR_BLACK "Unit Test for Linear Search toward List: " COLOR_RED "FAIL" COLOR_BLACK << std::endl;
		std::cout << COLOR_BLACK "Error Code: " << COLOR_RED << err << COLOR_BLACK << std::endl;
		return -1;
	}
	std::cout << COLOR_BLACK "Unit Test for Linear Search toward List: " COLOR_GREEN "SUCCESS" COLOR_BLACK << std::endl;

	err = UnitTest_JumpSearch();
	if (err){
		std::cout << COLOR_BLACK "Unit Test for Jump Search toward List: " COLOR_RED "FAIL" COLOR_BLACK << std::endl;
		std::cout << COLOR_BLACK "Error Code: " << COLOR_RED << err << COLOR_BLACK << std::endl;
		return -1;
	}
	std::cout << COLOR_BLACK "Unit Test for Jump Search toward List: " COLOR_GREEN "SUCCESS" COLOR_BLACK << std::endl; 

	err = UnitTest_BinarySearch();
	if (err){
		std::cout << COLOR_BLACK "Unit Test for Binary Search toward List: " COLOR_RED "FAIL" COLOR_BLACK << std::endl;
		std::cout << COLOR_BLACK "Error Code: " << COLOR_RED << err << COLOR_BLACK << std::endl;
		return -1;
	}
	std::cout << COLOR_BLACK "Unit Test for Binary Search toward List: " COLOR_GREEN "SUCCESS" COLOR_BLACK << std::endl; 

	err = UnitTest_TimeMeasurement();
	if (err){
		std::cout << COLOR_BLACK "Unit Test for Time Measurement: " COLOR_RED "FAIL" COLOR_BLACK << std::endl;
		std::cout << COLOR_BLACK "Error Code: " << COLOR_RED << err << COLOR_BLACK << std::endl;
		return -1;
	}
	return 0;
}
