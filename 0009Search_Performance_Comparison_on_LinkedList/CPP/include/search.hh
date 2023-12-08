#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.hh"

//Type Definitions and Declarations
class NODE {
public:
	std::string name;
	int number;
	NODE *next, *prev;

	//Member Functions
	NODE(void);
	NODE(std::string &);
	~NODE(void);
	NODE *Random(void);
};

class LIST {
public:
	NODE *begin, *end;
	int size;

	//Member Functions
	LIST(void);
	~LIST(void);
	NODE &operator[](int);
	LIST *AddRandom(void);
	LIST *AddRandom(int);
	LIST *ChangeRandomElement(std::string &, int);
	LIST *Sort(void);
	LIST *Print(void);
	NODE &LinearSearch(std::string &);
	NODE &JumpSearch(std::string &);
	NODE &BinarySearch(std::string &);
};

//Function Declarations
int FindSqrt(int);

#endif
