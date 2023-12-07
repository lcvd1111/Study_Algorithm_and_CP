#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.hh"

//Type Definitions and Declarations
class NODE {
public:
	std::string name;
	int number;
	NODE *prev, *next;

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
	int Size(void);
	LIST *AddRandom(void);
	LIST *AddRandom(int);
	LIST *ChangeRandomElement(std::string &, int);
	void Print(void);
	LIST *Sort(void);
	NODE &Search(std::string &);
};

int FindSqrt(int);
#endif
