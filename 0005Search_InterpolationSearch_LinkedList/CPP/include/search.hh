#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.hh"

//Type Defintions and Declarations
class NODE {
public:
	//Member Variables
	std::string name;
	int number;
	NODE *prev, *next;

	//Member Functions
	NODE(void);
	NODE(std::string &, int);
	~NODE(void);
	NODE *Random(void);
};

class LIST {
private:
	//Member Variables
	int size;
public:
	//Member Variables
	NODE *begin, *end;

	//Member Functions
	LIST(void);
	~LIST(void);
	NODE &operator[](int);
	int Size(void);
	LIST *AddRandom(void);
	LIST *AddRandom(int);
	LIST *ChangeRandomElement(std::string &, int);
	LIST *Sort(void);
	void Print(void);
	NODE &Search(int);
};

#endif
