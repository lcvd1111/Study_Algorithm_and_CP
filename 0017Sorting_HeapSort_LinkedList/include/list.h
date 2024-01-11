#ifndef __LIST_HEADER__
#define __LIST_HEADER__

#include "common.h"
#include "node.h"
#include "heap.h"

//Type Declarations and Defintions
typedef struct _LIST LIST;

struct _LIST {
	NODE *begin, *end;
	int size;

	//Method Functions
	LIST *(*AddRandom)(LIST *);
	void (*Print)(LIST *);
	LIST *(*Sort)(LIST *);
	int (*Size)(LIST *);
	LIST *(*CopyArray)(LIST *, NODE **);
};

//Function Declarations
void LIST_CONSTRUCTOR(LIST *);
void LIST_DESTRUCTOR(LIST *);
LIST *LIST_METHOD_AddRandom(LIST *);
void LIST_METHOD_Print(LIST *);
LIST *LIST_METHOD_Sort(LIST *);
LIST *LIST_METHOD_CopyArray(LIST *, NODE **);
int LIST_METHOD_Size(LIST *);

#endif
