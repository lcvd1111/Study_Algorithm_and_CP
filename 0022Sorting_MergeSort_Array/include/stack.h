#ifndef __STACK_HEADER__
#define __STACK_HEADER__

#include "common.h"

//Defition and Declaration of data type.
typedef struct _STACK_NODE STACK_NODE;
typedef struct _STACK STACK;

struct _STACK_NODE {
	int begin_Index, end_Index;
	int status;
	STACK_NODE *prev, *next;
};

struct _STACK {
	//Member Variables.
	STACK_NODE *begin, *end;
	int size;

	//Member Functions.
	STACK *(*Push)(STACK *this, STACK_NODE *inputArg);
	STACK *(*Pop)(STACK *this, STACK_NODE *outputDest);
	int (*Size)(STACK *this);
};

//Declaration for functions for method
void STACK_METHOD_CONSTRUCTOR(STACK *this);
void STACK_METHOD_DESTRUCTOR(STACK *this);
STACK *STACK_METHOD_Push(STACK *this, STACK_NODE *inputArg);
STACK *STACK_METHOD_Pop(STACK *this, STACK_NODE *outputDest);

#endif
