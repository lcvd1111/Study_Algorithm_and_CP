#ifndef __ARRAY_HEADER__
#define __ARRAY_HEADER__

#include "common.h"
#define NAME_LEN 32

typedef struct _NODE NODE;
typedef struct _ARRAY ARRAY;

struct _NODE {
	//Member Variables
	char name[NAME_LEN];
	int number;

	//Member Functions
	void (*Random)(NODE *);
};

struct _ARRAY {
	//Member Variables
	NODE *nodeArray;
	int size;

	//Member Functions
	ARRAY *(*Fill_Random)(ARRAY *);
	void (*Print)(ARRAY *);
	ARRAY *(*Copy_to_Raw_Array)(ARRAY *, NODE **);
	ARRAY *(*Sort)(ARRAY *);
};

//Declaration for Member Functions of struct _NODE
void NODE_METHOD_CONSTRUCTOR(NODE *);
void NODE_METHOD_DESTRUCTOR(NODE *);
void NODE_METHOD_Random(NODE *);

//Declaration for Member Functions of struct _ARRAY
void ARRAY_METHOD_CONSTRUCTOR(ARRAY *, int);
void ARRAY_METHOD_DESTRUCTOR(ARRAY *);
ARRAY *ARRAY_METHOD_Fill_Random(ARRAY *);
void ARRAY_METHOD_Print(ARRAY *);
ARRAY *ARRAY_METHOD_Copy_to_Raw_Array(ARRAY *, NODE **);
ARRAY *ARRAY_METHOD_Sort(ARRAY *);

#endif
