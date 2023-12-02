#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.hh"

//Type Definitions and Declarations
class NODE {
	std::string name;
	int number;

	//Method Functions
	NODE(void);
	~NODE(void);
	NODE *Random(void);
};

class ARRAY{
	std::vector<NODE> nodeVector;

	//Method Functions
	ARRAY(void);
	~ARRAY(void);
	NODE &operator[](int);
	int Size(void);
	ARRAY *AddRandom(void);
	ARRAY *AddRandom(int);
	ARRAY *ChangeRandomElement(std::string &, int);
	ARRAY *Sort(void);
	NODE &Search(int);
};

#endif
