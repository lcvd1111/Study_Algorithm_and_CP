#ifndef __HEAP_HEADER__
#define __HEAP_HEADER__

#include "common.h"

//Type Definitions
typedef struct _HEAP_NODE HEAP_NODE;
typedef struct _HEAP HEAP;
typedef struct _HEAP_METHOD HEAP_METHOD;

struct _HEAP_NODE {
	//Member Variables
	char name[NAME_LEN];
	int number;

	//Member Functions
};

struct _HEAP_METHOD {
	int (*Enqueue)(HEAP *, char *, int);
	int (*Dequeue)(HEAP *, HEAP_NODE *);
};

struct _HEAP {
	//Member Variables
	HEAP_NODE *heapArray;
	int size;
	int level;
	int currentLastIndex;

	//Member Functions
	HEAP_METHOD *Method;
};


//Function Declarations for methods
void HEAP_NODE_METHOD_CONSTRUCTOR(HEAP_NODE *this);
void HEAP_NODE_METHOD_DESTRUCTOR(HEAP_NODE *this);

void HEAP_METHOD_CONSTRUCTOR(HEAP *this, int);
void HEAP_METHOD_DESTRUCTOR(HEAP *this);
int HEAP_METHOD_Enqueue(HEAP *this, char *, int);
int HEAP_METHOD_Dequeue(HEAP *this, HEAP_NODE *dest);

#endif
