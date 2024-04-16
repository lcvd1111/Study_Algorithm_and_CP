#ifndef __ARRAY_HEADER__
#define __ARRAY_HEADER__

#include "common.h"

typedef struct _NODE_METHOD NODE_METHOD;
typedef struct _NODE NODE;
typedef struct _ARRAY_METHOD ARRAY_METHOD;
typedef struct _ARRAY ARRAY;

struct _NODE {
	//Member Variables
	char name[NAME_LEN];
	int number;

	//Member Functions
	NODE_METHOD *Method;
};

struct _NODE_METHOD {
	void (*Random)(NODE *);
};

struct _ARRAY {
	//Member Variables
	NODE *nodeArray;
	int size;
	int currentIndex;

	//Member Functions
	ARRAY_METHOD *Method;
};

struct _ARRAY_METHOD {
	ARRAY *(*Fill_Random)(ARRAY *);
	void (*Print)(ARRAY *);
	ARRAY *(*Copy_to_Array)(ARRAY *, ARRAY *);
	ARRAY *(*Copy_to_Raw_Array)(ARRAY *, NODE *);
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
ARRAY *ARRAY_METHOD_Copy_to_Array(ARRAY *, ARRAY *);
ARRAY *ARRAY_METHOD_Copy_to_Raw_Array(ARRAY *, NODE *);
ARRAY *ARRAY_METHOD_Sort(ARRAY *);

#endif
