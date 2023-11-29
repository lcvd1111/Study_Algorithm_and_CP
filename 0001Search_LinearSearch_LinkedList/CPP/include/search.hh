#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.hh"

#define NAME_LEN 16

//Type Definitions and Declarations
typedef class _NODE NODE;
typedef class _LIST LIST;

class _NODE {
public:
	//Member variables
	std::string name;
	int number;
	NODE *prev, *next;
	
	//Member functions
	_NODE(void);
	~_NODE(void);
	NODE *Random(void);
};

class _LIST {
public:
	//Member variables
	NODE *begin, *end;
	int size;

	//Member functions
	_LIST(void);
	~_LIST(void);
	LIST *AddRandom(void);
	LIST *AddRandom(int );
	LIST *ChangeRandomElement(std::string &, int);
	NODE *Search(std::string &);
	LIST *Clear(void);
	void Print(void);
	NODE &operator[](int);
};

#endif
