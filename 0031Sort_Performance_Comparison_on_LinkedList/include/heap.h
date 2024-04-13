#ifndef __BINARY_HEAP_HEADER__
#define __BINARY_HEAP_HEADER__

#include "common.h"

//Type Declarations and Definitions
typedef struct _BINARY_HEAP_NODE BINARY_HEAP_NODE;
typedef BINARY_HEAP_NODE PQ_NODE;
typedef struct _BINARY_HEAP BINARY_HEAP;
typedef BINARY_HEAP HEAP;
typedef HEAP PQ;

struct _BINARY_HEAP_NODE {
	char name[NAME_LEN];
	int number;
};

struct _BINARY_HEAP {
	BINARY_HEAP_NODE *heapArray;
	int level;
	int size;
	int lastIndex;

	//Method Functions
	PQ *(*Enqueue)(PQ *, BINARY_HEAP_NODE *);
	PQ *(*Dequeue)(PQ *, BINARY_HEAP_NODE *);
};

//Function Declarations
void PQ_CONSTRUCTOR(PQ *, int);
void PQ_DESTRUCTOR(PQ *);
PQ *PQ_METHOD_Enqueue(PQ *, BINARY_HEAP_NODE *);
PQ *PQ_METHOD_Dequeue(PQ *, BINARY_HEAP_NODE *dest);

#endif
