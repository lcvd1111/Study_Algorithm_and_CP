#ifndef __BINARY_HEAP_HEADER__
#define __BINARY_HEAP_HEADER__

#include "common.h"
#include "node.h"

//Type Declarations and Definitions
typedef struct _BINARY_HEAP BINARY_HEAP;
typedef BINARY_HEAP HEAP;
typedef HEAP PQ;

struct _BINARY_HEAP {
	NODE **heapArray; //Array whose each element's type is 'NODE *'.
	int level;
	int size;
	int lastIndex;

	//Method Functions
	PQ *(*Enqueue)(PQ *, NODE *);
	NODE *(*Dequeue)(PQ *);
};

//Function Declarations
void PQ_CONSTRUCTOR(PQ *, int);
void PQ_DESTRUCTOR(PQ *);
PQ *PQ_METHOD_Enqueue(PQ *, NODE *);
NODE *PQ_METHOD_Dequeue(PQ *);

#endif
