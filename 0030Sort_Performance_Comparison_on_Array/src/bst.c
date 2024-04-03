#include "bst.h"

//Global Variables for Methods
BST_METHOD gBstMethod = {.Insert = &BST_METHOD_Insert };

//Function Definitions for methods
void BST_NODE_METHOD_CONSTRUCTOR(BST_NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Initializing member variables
	memset(this->key, 0, NAME_LEN);
	this->data = 0;
	this->leftChild = this->rightChild = NULL;
	this->nextFriend = NULL;

	return ;
}

void BST_NODE_METHOD_DESTRUCTOR(BST_NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	return ;
}

void BST_METHOD_CONSTRUCTOR(BST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Initializing member variables
	this->root = NULL;
	this->size = 0;

	//Binding methods(=member functions)
	this->Method = &gBstMethod;

	return ;
}

int DFS_Postorder_Traversal_Destruction(BST *this, BST_NODE *inputNode)
{
	BST_NODE *currentNode = inputNode;
	BST_NODE *tempNode = NULL;

	//Exception Handling
	if (inputNode == NULL){
		PRINTF_ERROR("ERROR: 'inputNode' is NULL.\n");
		return -1;
	}

	if (currentNode->leftChild != NULL){
		DFS_Postorder_Traversal_Destruction(this, currentNode->leftChild);
	}

	if (currentNode->rightChild != NULL){
		DFS_Postorder_Traversal_Destruction(this, currentNode->rightChild);
	}

	while(currentNode->nextFriend != NULL){
		tempNode = currentNode->nextFriend;
		BST_NODE_METHOD_DESTRUCTOR(currentNode);
		free(currentNode);
		this->size -= 1;
		currentNode = tempNode;
	}

	BST_NODE_METHOD_DESTRUCTOR(currentNode);
	free(currentNode);
	this->size -= 1;

	return 0;
}

void BST_METHOD_DESTRUCTOR(BST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	if (this->root == NULL){
		assert(this->size == 0);
		return ;
	}

	DFS_Postorder_Traversal_Destruction(this, this->root);
	assert(this->size == 0);

	return ;
}

BST *BST_METHOD_Insert(BST *this, char *inputName, int inputNumber)
{
	BST_NODE *currentNode = NULL;
	BST_NODE *tempNode = NULL;
	int compareResult = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the tree is empty currently.
	if (this->root == NULL){
		assert(this->size == 0);
		this->root = (BST_NODE *)malloc(sizeof(BST_NODE));
		BST_NODE_METHOD_CONSTRUCTOR(this->root);
		this->size += 1;
		memcpy(this->root->key, inputName, NAME_LEN);
		this->root->data = inputNumber;
		return this;
	}

	currentNode = this->root;
	while(1){
		compareResult = strcmp(currentNode->key, inputName);
		if (compareResult > 0){
			if (currentNode->leftChild != NULL){
				currentNode = currentNode->leftChild;
				continue;
			}
			else{
				currentNode->leftChild = (BST_NODE *)malloc(sizeof(BST_NODE));
				BST_NODE_METHOD_CONSTRUCTOR(currentNode->leftChild);
				memcpy(currentNode->leftChild->key, inputName, NAME_LEN);
				currentNode->leftChild->data = inputNumber;
				this->size += 1;
				return this;
			}
		}
		else if (compareResult == 0){
			while(currentNode->nextFriend != NULL){
				currentNode = currentNode->nextFriend;
			}
			currentNode->nextFriend = (BST_NODE *)malloc(sizeof(BST_NODE));
			BST_NODE_METHOD_CONSTRUCTOR(currentNode->nextFriend);
			memcpy(currentNode->nextFriend->key, inputName, NAME_LEN);
			currentNode->nextFriend->data = inputNumber;
			this->size += 1;
			return this;
		}
		else if (compareResult < 0){
			if (currentNode->rightChild != NULL){
				currentNode = currentNode->rightChild;
				continue;
			}
			else{
				currentNode->rightChild = (BST_NODE *)malloc(sizeof(BST_NODE));
				BST_NODE_METHOD_CONSTRUCTOR(currentNode->rightChild);
				memcpy(currentNode->rightChild->key, inputName, NAME_LEN);
				currentNode->rightChild->data = inputNumber;
				this->size += 1;
				return this;
			}
		}
	}

	return this;
}
