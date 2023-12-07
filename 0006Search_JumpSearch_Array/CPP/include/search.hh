#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.hh"

//Type Definitions and Delcarations
class NODE {
public:
	//Member variables
	std::string name;
	int number;

	//Member functions
	NODE(void);
	NODE(std::string &);
	~NODE(void);
	NODE *Random(void);
};

class ARRAY {
public:
	//Member variables
	std::vector<NODE> nodeVector;

	//Member functions
	ARRAY(void);
	~ARRAY(void);
	NODE &operator[](int);
	int Size(void);
	ARRAY *AddRandom(void);
	ARRAY *AddRandom(int);
	ARRAY *ChangeRandomElement(std::string &, int);
	ARRAY *Sort(void);
	NODE &Search(std::string &);
	void Print(void);
};

//Function Declarations
int FindSqrt(int );
#endif
