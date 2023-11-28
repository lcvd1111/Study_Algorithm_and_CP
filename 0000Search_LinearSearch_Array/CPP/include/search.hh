#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.hh"

//Type Definitions and Declarations
class NODE {
public:
	//Member variables
	std::string name;
	int number;

	//Member functions
	NODE(void);
	~NODE(void);
	NODE *Random(void);
};

class VECTOR {
public:
	//Member variables
	std::vector<NODE> array;

	//Member functions
	VECTOR(void);
	~VECTOR(void);
	int Add(void);//push back random member.
	int Add(std::string &, int);//change one of element into inpute data.
	NODE &operator[](int);
	NODE Search(std::string &);
	void Print(void);
};

#endif
