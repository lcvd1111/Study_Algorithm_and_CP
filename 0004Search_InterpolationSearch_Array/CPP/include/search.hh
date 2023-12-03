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
	NODE(std::string);
	~NODE(void);
	NODE *Random(void);
};

class ARRAY{
public:
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
	void Print(void);
	NODE &Search(int);
};

#endif
