#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.hh"

//Type Definitions
class NODE {
public:
	std::string name;
	int number;

	//Method Functions
	NODE(void);
	NODE(std::string &);
	~NODE(void);
	NODE *Random(void);
};

class ARRAY {
public:
	std::vector<NODE> nodeArray;

	//Method Functions
	ARRAY(void);
	~ARRAY(void);
	NODE &operator[](int);
	void Print(void);
	int Size(void);
	void Sort(void);
	ARRAY *AddRandom(void);
	ARRAY *AddRandom(int);
	ARRAY *ChangeRandomElement(std::string &, int);
	NODE &LinearSearch(std::string &);
	NODE &JumpSearch(std::string &);
	NODE &BinarySearch(std::string &);
};

//Function Declarations
int FindSqrt(int);

#endif
