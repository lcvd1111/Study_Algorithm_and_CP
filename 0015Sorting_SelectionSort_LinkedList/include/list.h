#ifndef __LIST_HEADER__
#define __LIST_HEADER__

#include "common.h"

#define NAME_LEN 32

//Type Definitions and Declarations
typedef struct _NODE NODE;
typedef struct _LIST LIST;

struct _NODE {
	char name[NAME_LEN];
	int number;
	NODE *prev, *next;

	//Method functions
	NODE *(*Random)(NODE *);
};

struct _LIST {
	NODE *begin, *end;
	int size;

	//Method functions
	LIST *(*AddRandom)(LIST *);
	LIST *(*ChangeRandomElement)(LIST *, char *, int);
	int (*Size)(LIST *);
	LIST *(*CopyArray)(LIST *, NODE **);
	void (*Print)(LIST *);
	LIST *(*Sort)(LIST *);
};

//Functino Declarations
void NODE_CONSTRUCTOR(NODE *);
void NODE_DESTRUCTOR(NODE *);
NODE *NODE_METHOD_Random(NODE *);

void LIST_CONSTRUCTOR(LIST *);
void LIST_DESTRUCTOR(LIST *);
LIST *LIST_METHOD_AddRandom(LIST *);
LIST *LIST_METHOD_ChangeRandomElement(LIST *, char *, int);
int LIST_METHOD_Size(LIST *);
LIST *LIST_METHOD_CopyArray(LIST *, NODE **);
void LIST_METHOD_Print(LIST *);
LIST *LIST_METHOD_Sort(LIST *);

#endif
