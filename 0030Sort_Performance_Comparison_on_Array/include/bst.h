#ifndef __BST_HEADER__
#define __BST_HEADER__

#include "common.h"

//Type Definitions
typedef struct _BST_NODE BST_NODE;
typedef struct _BST BST;
typedef struct _BST_METHOD BST_METHOD;

struct _BST_NODE {
	//Member Variables
	char key[NAME_LEN];
	int data;
	BST_NODE *leftChild, *rightChild;
	BST_NODE *nextFriend;

	//Member Functions
};

struct _BST {
	//Member Variables
	BST_NODE *root;
	int size;

	//Member Functions
	BST_METHOD *Method;
};

struct _BST_METHOD {
	BST *(*Insert)(BST *this, char *inputName, int inputNum);
};

//Function Declarations for methods
void BST_NODE_METHOD_CONSTRUCTOR(BST_NODE *this);
void BST_NODE_METHOD_DESTRUCTOR(BST_NODE *this);

void BST_METHOD_CONSTRUCTOR(BST *this);
void BST_METHOD_DESTRUCTOR(BST *this);
BST *BST_METHOD_Insert(BST *this, char *inputName, int inputNumber);

#endif
