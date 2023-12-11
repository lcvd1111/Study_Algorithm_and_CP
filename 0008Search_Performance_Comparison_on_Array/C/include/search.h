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

	//Method Functions
	NODE *(*Random)(NODE *);
};

struct _ARRAY {
	NODE *nodeArray;
	int size;

	//Method Functions
	void (*Print)(ARRAY *);
	void (*Sort)(ARRAY *);
	ARRAY *(*FillRandom)(ARRAY *);
	ARRAY *(*ChangeRandomElement)(ARRAY *, char *, int);
	NODE *(*LinearSearch)(ARRAY *, char *);
	NODE *(*JumpSearch)(ARRAY *, char *);
	NODE *(*BinarySearch)(ARRAY *, char *);
};

//Function Declarations
void NODE_CONSTRUCTOR(NODE *);
void NODE_DESTRUCTOR(NODE *);
NODE *NODE_METHOD_Random(NODE *);

void ARRAY_CONSTRUCTOR(ARRAY *, int);
void ARRAY_DESTRUCTOR(ARRAY *);
void ARRAY_METHOD_Print(ARRAY *);
void ARRAY_METHOD_Sort(ARRAY *);
ARRAY *ARRAY_METHOD_FillRandom(ARRAY *);
ARRAY *ARRAY_METHOD_ChangeRandomElement(ARRAY *, char *, int);
NODE *ARRAY_METHOD_LinearSearch(ARRAY *, char *);
NODE *ARRAY_METHOD_JumpSearch(ARRAY *, char *);
NODE *ARRAY_METHOD_BinarySearch(ARRAY *, char *);
int FindSqrt(int);

#endif
