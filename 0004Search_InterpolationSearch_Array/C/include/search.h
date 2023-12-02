#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.h"

#define NAME_LEN 32

//Type Definitions and Declarations
typedef struct _NODE NODE;
typedef struct _ARRAY ARRAY;

struct _NODE {
	char name[NAME_LEN];
	int number;

	//Memeber Functions
	NODE *(*Random)(NODE *);
};

struct _ARRAY {
	NODE *nodeArray;
	int size;

	//Member Functions
	ARRAY *(*FillRandom)(ARRAY *);
	ARRAY *(*ChangeRandomElement)(ARRAY *, char *, int);
	ARRAY *(*Sort)(ARRAY *);
	int (*Size)(ARRAY *);
	NODE *(*Search)(ARRAY *, int);
	void (*Print)(ARRAY *);
};

//Function Declarations
void NODE_CONSTRUCTOR(NODE *);
void NODE_DESTRUCTOR(NODE *);
NODE *NODE_METHOD_Random(NODE *);

void ARRAY_CONSTRUCTOR(ARRAY *, int);
void ARRAY_DESTRUCTOR(ARRAY *);
ARRAY *ARRAY_METHOD_FillRandom(ARRAY *);
ARRAY *ARRAY_METHOD_ChangeRandomElement(ARRAY *, char *, int);
ARRAY *ARRAY_METHOD_Sort(ARRAY *);
int ARRAY_METHOD_Size(ARRAY *);
NODE *ARRAY_METHOD_Search(ARRAY *, int);
void ARRAY_METHOD_Print(ARRAY *);

#endif
