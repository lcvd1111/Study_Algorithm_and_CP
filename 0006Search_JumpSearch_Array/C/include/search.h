#ifndef __SEARCH_HEADER__
#define __SEARCH_HEADER__

#include "common.h"
#define NAME_LEN 32

//Type Definitions and Declarations
typedef struct _NODE NODE;
typedef struct _ARRAY ARRAY;

struct _NODE {
	//Member variables
	char name[NAME_LEN];
	int number;

	//Member Functions
	NODE *(*Random)(NODE *);
};

struct _ARRAY {
	//Member variables
	NODE *nodeArray;
	int size;

	//Member Functions
	ARRAY *(*FillRandom)(ARRAY *);
	ARRAY *(*ChangeRandomElement)(ARRAY *, char *, int);
	void (*Print)(ARRAY *);
	ARRAY *(*Sort)(ARRAY *);
	NODE *(*Search)(ARRAY *, char *);
};

//Function Declarations
void NODE_CONSTRUCTOR(NODE *);
void NODE_DESTRUCTOR(NODE *);
NODE *NODE_METHOD_Random(NODE *);

void ARRAY_CONSTRUCTOR(ARRAY *, int);
void ARRAY_DESTRUCTOR(ARRAY *);
ARRAY *ARRAY_METHOD_FillRandom(ARRAY *);
ARRAY *ARRAY_METHOD_ChangeRandomElement(ARRAY *, char *, int);
void ARRAY_METHOD_Print(ARRAY *);
ARRAY *ARRAY_METHOD_Sort(ARRAY *);
NODE *ARRAY_METHOD_Search(ARRAY *, char *);

#endif
