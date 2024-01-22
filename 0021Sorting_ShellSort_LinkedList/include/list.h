#ifndef __LIST_HEADER__
#define __LIST_HEADER__

#include "common.h"

#define NAME_LEN 32

//Type Declarations and Definitions
typedef struct _NODE NODE;
typedef struct _LIST LIST;

struct _NODE {
	char name[NAME_LEN];
	int number;
	NODE *prev, *next;

	//Method Functions
	NODE *(*Random)(NODE *);
};

struct _LIST {
	NODE *begin, *end;
	int size;

	//Method Functions
	LIST *(*AddRandom)(LIST *);
	void (*Print)(LIST *);
	LIST *(*CopyRawArray)(LIST *, NODE **);
	LIST *(*Sort)(LIST *);
};

//Function Declarations
void NODE_CONSTRUCTOR(NODE *);
void NODE_DESTRUCTOR(NODE *);
NODE *NODE_METHOD_Random(NODE *);

void LIST_CONSTRUCTOR(LIST *);
void LIST_DESTRUCTOR(LIST *);
LIST *LIST_METHOD_AddRandom(LIST *);
void LIST_METHOD_Print(LIST *);
LIST *LIST_METHOD_CopyRawArray(LIST *, NODE **);
LIST *LIST_METHOD_Sort(LIST *);

#endif
