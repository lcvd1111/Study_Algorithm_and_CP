#include "bst.h"

//Declarations of Functions for methods.
void BST_NODE_METHOD_CONSTRUCTOR(BST_NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

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

	this->leftChild = this->rightChild = this->nextFriend = NULL;

	return ;
}


void BST_METHOD_CONSTRUCTOR(BST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	this->root = NULL;
	this->size = 0;

	//Binding the method functions
	this->Insert = &BST_METHOD_Insert;

	return ;
}

int DFS_Destruction(BST *this, BST_NODE *inputNode){
	BST_NODE *currentNode = inputNode;
	BST_NODE *tempNode = NULL;

	if (currentNode->leftChild != NULL){
		DFS_Destruction(this, currentNode->leftChild);
	}
	
	if (currentNode->rightChild != NULL){
		DFS_Destruction(this, currentNode->rightChild);
	}

	while (currentNode->nextFriend != NULL){
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

int Recursive_Destruction(BST *this)
{
	if(DFS_Destruction(this, this->root)){
		return -1;
	}

	return 0;
}

void BST_METHOD_DESTRUCTOR(BST *this)
{
	int errCode = 0;

	//Exception Handling
	if (this == NULL){
		return ;
	}

	if (this->root == NULL){
		assert(this->size == 0);
		return ;
	}

	//Post-Order Traversal for destroying binary tree.
	if(errCode = Recursive_Destruction(this)){
		PRINTF_ERROR("Recursive_Destruction Failed.\n"
				"Error Code: %d\n", errCode);
		return ;
	}

	assert(this->size == 0);

	return ;
}


BST *BST_METHOD_Insert(BST *this, char *inputKey, int inputData)
{
	BST_NODE *currentNode = NULL;
	int cmpResult = 0;
	
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	if (this->root == NULL){
		assert(this->size == 0);
		this->root = (BST_NODE *)malloc(sizeof(BST_NODE));
		BST_NODE_METHOD_CONSTRUCTOR(this->root);
		this->size += 1;
		memcpy(this->root->key, inputKey, NAME_LEN);
		this->root->data = inputData;
		return this;
	}

	currentNode = this->root;

	while(1){
		cmpResult = strcmp(currentNode->key, inputKey);
		if (cmpResult == 0){
			while(currentNode->nextFriend != NULL){
				currentNode = currentNode->nextFriend;
			}
			currentNode->nextFriend = (BST_NODE *)malloc(sizeof(BST_NODE));
			BST_NODE_METHOD_CONSTRUCTOR(currentNode->nextFriend);
			this->size += 1;
			memcpy(currentNode->nextFriend->key, inputKey, NAME_LEN);
			currentNode->nextFriend->data = inputData;
			return this;
		}

		if (cmpResult<0){
			if (currentNode->rightChild != NULL){
				currentNode = currentNode->rightChild;
				continue;
			}
			assert(currentNode->rightChild == NULL);
			currentNode->rightChild = (BST_NODE *)malloc(sizeof(BST_NODE));
			BST_NODE_METHOD_CONSTRUCTOR(currentNode->rightChild);
			this->size += 1;
			memcpy(currentNode->rightChild->key, inputKey, NAME_LEN);
			currentNode->rightChild->data = inputData;
			return this;
		}

		if (cmpResult>0){
			if (currentNode->leftChild != NULL){
				currentNode = currentNode->leftChild;
				continue;
			}
			assert(currentNode->leftChild == NULL);
			currentNode->leftChild = (BST_NODE *)malloc(sizeof(BST_NODE));
			BST_NODE_METHOD_CONSTRUCTOR(currentNode->leftChild);
			this->size += 1;
			memcpy(currentNode->leftChild->key, inputKey, NAME_LEN);
			currentNode->leftChild->data = inputData;
			return this;
		}

		PRINTF_ERROR("ERROR: Unexpected situation occured.\n");
		return NULL;
	}

	return this;
}
