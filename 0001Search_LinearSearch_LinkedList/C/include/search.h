#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.h"

#define NAME_LEN 15

//Type definitions and declarations
typedef struct _NODE NODE;
typedef struct _LIST LIST;

struct _NODE {
	//Member variables
	char name[NAME_LEN];
	int number;
	NODE *next;
	NODE *prev;

	//Member functions
	NODE *(*Random)(NODE *);
};

struct _LIST {
	//Member variables
	NODE *begin;
	NODE *end;

	//Member functions
	NODE *(*Index)(LIST *, int);
	LIST *(*Add)(LIST *);
	LIST *(*Change)(LIST *, char *, int);
	LIST *(*Clear)(LIST *);
};

//Function Declarations
void NODE_CONSTRUCTOR(NODE *);
void NODE_DESTRUCTOR(NODE *);
NODE *NODE_METHOD_Random(NODE *);
void LIST_CONSTRUCTOR(LIST *);
void LIST_DESTRUCTOR(LIST *);
LIST *LIST_METHOD_Add(LIST *);
LIST *LIST_METHOD_Change(LIST *, char *, int);
NODE *LIST_METHOD_Index(LIST *, int);

#endif
