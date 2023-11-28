#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.h"

#define STRING_LEN 32

//Type Defintions and Declarations
typedef struct _NODE NODE;
struct _NODE {
	char name[STRING_LEN];
	int number;
};

//Function Declarations
NODE *RandomFill(NODE *arrayArg, int sizeArg);
int LinearSearch(NODE *arrayArg, int sizeArg, char *nameArg);

#endif
