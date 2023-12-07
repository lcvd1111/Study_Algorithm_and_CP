#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.h"

#define NAME_LEN 32

//Type Definitions and Declarations
typedef struct _NODE NODE;
typedef struct _LIST LIST;

struct _NODE {
	char name[NAME_LEN];
	int number;
	NODE *prev, *next;

	//Member functions
	NODE *(*Random)(NODE *);
};

struct _LIST {
	NODE *begin;
	NODE *end;
	int size;

	//Member fucntions
	LIST *(*AddRandom)(LIST *);
	LIST *(*ChangeRandomElement)(LIST *, char *, int);
	void (*Print)(LIST *);
	LIST *(*Sort)(LIST *);
	int (*Size)(LIST *);
	NODE *(*Search)(LIST *, char *);
};

//Function definitinos
void NODE_CONSTRUCTOR(NODE *);
void NODE_DESTRCTOR(NODE *);
NODE *NODE_METHOD_Random(NODE *);

void LIST_CONSTRUCTOR(LIST *);
void LIST_DESTRUCTOR(LIST *);
LIST *LIST_METHOD_AddRandom(LIST *);
LIST *LIST_METHOD_ChangeRandomElement(LIST *, char *, int);
void LIST_METHOD_Print(LIST *);
LIST *LIST_METHOD_Sort(LIST *);
int LIST_METHOD_Size(LIST *);
NODE *LIST_METHOD_Search(LIST *, char *);
int FindSqrt(int);

#endif
