#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.hh"

//Type Defintions and Declarations
class NODE {
public:
	std::string name;
	int number;
	NODE *prev, *next;

	//Method Functions
	NODE(void);
	~NODE(void);
	NODE *Random(void);
};

class LIST {
public:
	NODE *begin, *end;
	int size;

	//Method Functions
	LIST(void);
	~LIST(void);
	NODE &operator[](int);
	void Print(void);
	LIST *AddRandom(void);
	LIST *AddRandom(int);
	LIST *ChangeRandomElement(std::string &, int);
	LIST *Sort(void);
	NODE &Search(std::string &);
};

#endif
