#ifndef __LINKED_LIST_HEADER__
#define __LINKED_LIST_HEADER__

#include "common.h"

#define NAME_LEN 32

//Type Definitions and Declarations
typedef struct _NODE NODE;
typedef struct _LIST LIST;

struct _NODE {
	//Member Variables
	char name[NAME_LEN];
	int number;
	NODE *prev, *next;

	//Method Functions
	NODE *(*Random)(NODE *);
};

struct _LIST {
	//Member Variables
	NODE *begin, *end;
	int size;

	//Method Functions
	int (*Size)(LIST *);
	LIST *(*Push)(LIST *);
	LIST *(*AddRandom)(LIST *, int);
	LIST *(*ChangeRandomElement)(LIST *, char *, int);
	void (*Print)(LIST *);
	LIST *(*Sort)(LIST *);
	LIST *(*Swap)(LIST *, NODE *, NODE *);
};

//Function Declarations
void NODE_CONSTRUCTOR(NODE *);
void NODE_DESTRUCTOR(NODE *);
NODE *NODE_METHOD_Random(NODE *);

void LIST_CONSTRUCTOR(LIST *);
void LIST_DESTRUCTOR(LIST *);
int LIST_METHOD_Size(LIST *);
LIST *LIST_METHOD_Push(LIST *);
LIST *LIST_METHOD_AddRandom(LIST *, int);
LIST *LIST_METHOD_ChangeRandomElement(LIST *, char *, int);
void LIST_METHOD_Print(LIST *);
LIST *LIST_METHOD_Sort(LIST *);
LIST *LIST_METHOD_Swap(LIST *, NODE *, NODE *);

#endif
