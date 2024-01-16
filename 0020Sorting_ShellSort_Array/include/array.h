#ifndef __ARRAY_HEADER__
#define __ARRAY_HEADER__

#include "common.h"

#define NAME_LEN 32

//Type Defintions and Declarations
typedef struct _NODE NODE;
typedef struct _ARRAY ARRAY;

struct _NODE {
	char name[NAME_LEN];
	int number;

	//Method Functions
	NODE *(*Random)(NODE *);
};

struct _ARRAY {
	NODE *nodeArray;
	int size;

	//Method Functions
	ARRAY *(*FillRandom)(ARRAY *);
	void (*Print)(ARRAY *);
	ARRAY *(*CopyRawArray)(ARRAY *, NODE **);
	ARRAY *(*Sort)(ARRAY *);
};

//Function Declarations
void NODE_CONSTRUCTOR(NODE *);
void NODE_DESTRUCTOR(NODE *);
NODE *NODE_METHOD_Random(NODE *);

void ARRAY_CONSTRUCTOR(ARRAY *, int);
void ARRAY_DESTRUCTOR(ARRAY *);
ARRAY *ARRAY_METHOD_FillRandom(ARRAY *);
void ARRAY_METHOD_Print(ARRAY *);
ARRAY *ARRAY_METHOD_CopyRawArray(ARRAY *, NODE **);
ARRAY *ARRAY_METHOD_Sort(ARRAY *);
#endif
