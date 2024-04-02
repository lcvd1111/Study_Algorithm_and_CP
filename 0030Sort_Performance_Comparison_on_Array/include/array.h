#ifndef __ARRAY_HEADER__
#define __ARRAY_HEADER__

#include "common.h"
#include "heap.h"
#include "bst.h"

typedef struct _NODE_METHOD NODE_METHOD;
typedef struct _NODE NODE;
typedef struct _ARRAY_METHOD ARRAY_METHOD;
typedef struct _ARRAY_METHOD_SORT ARRAY_METHOD_SORT;
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
	ARRAY_METHOD_SORT *Sort;
};

struct _ARRAY_METHOD_SORT {
	ARRAY *(*Bubble_Sort)(ARRAY *);
	ARRAY *(*Insertion_Sort)(ARRAY *);
	ARRAY *(*Selection_Sort)(ARRAY *);
	ARRAY *(*Heap_Sort)(ARRAY *);
	ARRAY *(*Tree_Sort)(ARRAY *);
	ARRAY *(*Quick_Sort)(ARRAY *);
	ARRAY *(*Merge_Sort)(ARRAY *);
	ARRAY *(*Shell_Sort)(ARRAY *);
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
ARRAY *ARRAY_METHOD_Sort_Bubble(ARRAY *);
ARRAY *ARRAY_METHOD_Sort_Insertion(ARRAY *);
ARRAY *ARRAY_METHOD_Sort_Selection(ARRAY *);
ARRAY *ARRAY_METHOD_Sort_Heap(ARRAY *);
ARRAY *ARRAY_METHOD_Sort_Tree(ARRAY *);
ARRAY *ARRAY_METHOD_Sort_Quick(ARRAY *);
ARRAY *ARRAY_METHOD_Sort_Merge(ARRAY *);
ARRAY *ARRAY_METHOD_Sort_Shell(ARRAY *);

#endif
