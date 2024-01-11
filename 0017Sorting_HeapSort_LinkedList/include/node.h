#ifndef __NODE_HEADER__
#define __NODE_HEADER__

#include "common.h"

#define NAME_LEN 32

//Type Declarations and Definitions
typedef struct _NODE NODE;

struct _NODE {
	char name[NAME_LEN];
	int number;
	NODE *prev, *next;

	//Method functions
	NODE *(*Random)(NODE *);
};

void NODE_CONSTRUCTOR(NODE *);
void NODE_DESTRUCTOR(NODE *);
NODE *NODE_METHOD_Random(NODE *);

#endif
