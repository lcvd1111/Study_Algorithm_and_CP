#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.hh"

//Type Definitions and Declarations
class NODE {
public:
	std::string name;
	int number;
	
	//Method Functions
	NODE(void);
	~NODE(void);
	NODE *Random(void);
};

class ARRAY {
public:
	std::vector<NODE> nodeArray;

	//Method Functions
	ARRAY(void);
	~ARRAY(void);
	int Size(void);
	NODE &operator[](int);
	ARRAY *AddRandom(void);
	ARRAY *AddRandom(int);
	NODE &ChangeRandomElement(std::string &, int);
	ARRAY *Print(void);
	ARRAY *Sort(void);
	NODE &BinarySearch(std::string &);
};

#endif
