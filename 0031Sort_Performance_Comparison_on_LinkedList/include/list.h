#ifndef __LIST_HEADER__
#define __LIST_HEADER__

#include "common.h"
#include "heap.h"
#include "bst.h"

//Type Declarations and Definitions
typedef struct _LIST_NODE LIST_NODE;
typedef struct _LIST_NODE_METHOD LIST_NODE_METHOD;
typedef struct _LIST LIST;
typedef struct _LIST_METHOD LIST_METHOD;
typedef struct _LIST_METHOD_SORT LIST_METHOD_SORT;

struct _LIST_NODE {
	//Member Variables
	char name[NAME_LEN];
	int number;
	LIST_NODE *prev, *next;

	//Member Functions
	LIST_NODE_METHOD *Method;
};

struct _LIST_NODE_METHOD {
	void (*Random)(LIST_NODE *this);
};

struct _LIST {
	//Member Variables
	LIST_NODE *begin, *end;
	int size;
	LIST_NODE *currentNode;
	
	//Member Functions
	LIST_METHOD *Method;
};

struct _LIST_METHOD {
	LIST *(*Print)(LIST *this);
	int (*Size)(LIST *);
	LIST *(*Add_One_Random)(LIST *this);
	LIST *(*Add_Random)(LIST *this, int sizeArg);
	LIST *(*Copy_to_Array)(LIST *this, LIST_NODE *dest);
	LIST *(*Copy_to_List)(LIST *this, LIST *dest);
	LIST_METHOD_SORT *Sort;
};

struct _LIST_METHOD_SORT {
	LIST *(*Bubble)(LIST *);
	LIST *(*Insertion)(LIST *);
	LIST *(*Selection)(LIST *);
	LIST *(*Tree)(LIST *);
	LIST *(*Heap)(LIST *);
	LIST *(*Merge)(LIST *);
	LIST *(*Quick)(LIST *);
	LIST *(*Shell)(LIST *);
};

//Function Declarations for method
void LIST_NODE_METHOD_CONSTRUCTOR(LIST_NODE *this);
void LIST_NODE_METHOD_DESTRUCTOR(LIST_NODE *this);
void LIST_NODE_METHOD_Random(LIST_NODE *this);

void LIST_METHOD_CONSTRUCTOR(LIST *this);
void LIST_METHOD_DESTRUCTOR(LIST *this);
LIST *LIST_METHOD_Print(LIST *this);
int LIST_METHOD_Size(LIST *);
LIST *LIST_METHOD_Add_One_Random(LIST *this);
LIST *LIST_METHOD_Add_Random(LIST *this, int sizeArg);
LIST *LIST_METHOD_Copy_to_Array(LIST *this, LIST_NODE *dest);
LIST *LIST_METHOD_Copy_to_List(LIST *this, LIST *dest);
LIST *LIST_METHOD_SORT_Bubble(LIST *this);
LIST *LIST_METHOD_SORT_Insertion(LIST *this);
LIST *LIST_METHOD_SORT_Selection(LIST *this);
LIST *LIST_METHOD_SORT_Tree(LIST *this);
LIST *LIST_METHOD_SORT_Heap(LIST *this);
LIST *LIST_METHOD_SORT_Merge(LIST *this);
LIST *LIST_METHOD_SORT_Quick(LIST *this);
LIST *LIST_METHOD_SORT_Shell(LIST *this);

#endif
