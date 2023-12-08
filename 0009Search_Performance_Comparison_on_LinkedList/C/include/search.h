#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.h"

#define NAME_LEN 32

//Type Definitions and Delcarations
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
	LIST *(*ChangeRandomElement)(LIST *, char *, int);
	LIST *(*Sort)(LIST *);
	void (*Print)(LIST *);
	int (*Size)(LIST *);
	NODE *(*LinearSearch)(LIST *, char *);
	NODE *(*JumpSearch)(LIST *, char *);
	NODE *(*BinarySearch)(LIST *, char *);
};

//Function Declarations
void NODE_CONSTRUCTOR(NODE *);
void NODE_DESTRUCTOR(NODE *);
NODE *NODE_METHOD_Random(NODE *);

void LIST_CONSTRUCTOR(LIST *);
void LIST_DESTRUCTOR(LIST *);
LIST *LIST_METHOD_AddRandom(LIST *);
LIST *LIST_METHOD_ChangeRandomElement(LIST *, char *, int);
LIST *LIST_METHOD_Sort(LIST *);
void LIST_METHOD_Print(LIST *);
int LIST_METHOD_Size(LIST *);
NODE *LIST_METHOD_LinearSearch(LIST *, char *);
NODE *LIST_METHOD_JumpSearch(LIST *, char *);
NODE *LIST_METHOD_BinarySearch(LIST *, char *);
int FindSqrt(int arg);

#endif
