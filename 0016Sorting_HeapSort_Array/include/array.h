#ifndef __ARRAY_HEADER__
#define __ARRAY_HEADER__

#include "common.h"
#include "node.h"
#include "heap.h"

//Type Defintions and Declarations
typedef struct _ARRAY ARRAY;

struct _ARRAY {
	NODE *nodeArray;
	int size;

	//Method Functions
	ARRAY *(*FillRandom)(ARRAY *);
	void (*Print)(ARRAY *);
	ARRAY *(*Sort)(ARRAY *);
	int (*Size)(ARRAY *);
};

//Function Declarations
void ARRAY_CONSTRUCTOR(ARRAY *, int);
void ARRAY_DESTRUCTOR(ARRAY *);
ARRAY *ARRAY_METHOD_FillRandom(ARRAY *);
void ARRAY_METHOD_Print(ARRAY *);
ARRAY *ARRAY_METHOD_Sort(ARRAY *);
int ARRAY_METHOD_Size(ARRAY *);

#endif
