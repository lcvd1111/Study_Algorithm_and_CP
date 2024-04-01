#ifndef __LIST_HEADER__
#define __LIST_HEADER__

#include "common.h"
#include "bst.h"

//Type Declarations and Definitions
typedef struct _LIST_NODE LIST_NODE;
typedef LIST_NODE NODE;
typedef struct _LIST LIST;

struct _LIST_NODE {
	//Member Variables
	char name[NAME_LEN];
	int number;
	LIST_NODE *prev, *next;

	//Member Functions
	void (*Random)(LIST_NODE *this);
};

struct _LIST {
	//Member Variables
	LIST_NODE *begin, *end;
	int size;
	LIST_NODE *currentNode;
	
	//Member Functions
	LIST *(*Print)(LIST *this);
	int (*Size)(LIST *);
	LIST *(*Add_One_Random)(LIST *this);
	LIST *(*Add_Random)(LIST *this, int sizeArg);
	LIST *(*Sort)(LIST *this);
	LIST *(*Copy_to_Array)(LIST *this, LIST_NODE *dest);
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
LIST *LIST_METHOD_Sort(LIST *this);
LIST *LIST_METHOD_Copy_to_Array(LIST *this, LIST_NODE *dest);

#endif
