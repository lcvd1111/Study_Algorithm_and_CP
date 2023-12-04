#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.h"

#define NAME_LEN 32

//Type Definitions and Declarations
typedef struct _NODE NODE;
typedef struct _LIST LIST;

struct _NODE {
	//Member variables
	char name[NAME_LEN];
	int number;
	NODE *prev, *next;

	//Member functions
	NODE *(*Random)(NODE *);
};

struct _LIST {
	//Member variables
	NODE *begin, *end;
	int size;

	//Member functions
	void (*Print)(LIST *);
	int (*Size)(LIST *);
	LIST *(*AddRandom)(LIST *);
	LIST *(*ChangeRandomElement)(LIST *, char *, int);
	LIST *(*Sort)(LIST *);
	NODE *(*Search)(LIST *, int);
};

//Function Declarations
//NODE class related functions
void NODE_CONSTRUCTOR(NODE *);
void NODE_DESTRUCTOR(NODE *);
NODE *NODE_METHOD_Random(NODE *);

//LIST class related functions
void LIST_CONSTRUCTOR(LIST *);
void LIST_DESTRUCTOR(LIST *);
void LIST_METHOD_Print(LIST *);
int LIST_METHOD_Size(LIST *);
LIST *LIST_METHOD_AddRandom(LIST *);
LIST *LIST_METHOD_ChangeRandomElement(LIST *, char *, int);
LIST *LIST_METHOD_Sort(LIST *);
NODE *LIST_METHOD_Search(LIST *, int);

#endif
