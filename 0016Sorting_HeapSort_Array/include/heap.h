#ifndef __HEAP_HEADER__
#define __HEAP_HEADER__

#include "common.h"
#include "node.h"

//Type Definitions and Declarations
typedef struct _BINARY_HEAP BINARY_HEAP;
typedef BINARY_HEAP HEAP;
typedef HEAP PRIORITY_QUEUE;
typedef PRIORITY_QUEUE PQ;

struct _BINARY_HEAP {
	NODE **nodeArray; //Element of each node has a type of 'NODE *'
	int size;
	int level;
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
