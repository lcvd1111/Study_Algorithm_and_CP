#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.h"

#define NAME_LEN 16

//Type Defintions and Declarations
typedef struct _NODE NODE;
typedef struct _ARRAY ARRAY;

struct _NODE {
	char name[NAME_LEN];
	int number;

	//Method functions
	NODE *(*Random)(NODE *);
};

struct _ARRAY {
	NODE *nodeArray;
	int size;

	//Method functions
	ARRAY *(*FillRandom)(ARRAY *);
	NODE *(*ChangeRandomElement)(ARRAY *, char *, int);
	int (*Size)(ARRAY *);
	ARRAY *(*Sort)(ARRAY *);
	NODE *(*Search)(ARRAY *, char *);
	void (*Print)(ARRAY *);
};

//Function Declarations
void NODE_CONSTRUCTOR(NODE *);
void NODE_DESTRUCTOR(NODE *);
NODE *NODE_METHOD_Random(NODE *);

void ARRAY_CONSTRUCTOR(ARRAY *, int);
void ARRAY_DESTRUCTOR(ARRAY *);
ARRAY *ARRAY_METHOD_FillRandom(ARRAY *);
NODE *ARRAY_METHOD_ChangeRandomElement(ARRAY *, char *, int);
int ARRAY_METHOD_Size(ARRAY *);
ARRAY *ARRAY_METHOD_Sort(ARRAY *);
NODE *ARRAY_METHOD_Search(ARRAY *, char *);
void ARRAY_METHOD_Print(ARRAY *);

#endif
