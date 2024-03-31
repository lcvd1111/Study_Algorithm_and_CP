#include "array.h"
#include "bst.h"

static const char letterCollection[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Function Defitions for struct _NODE
void NODE_METHOD_CONSTRUCTOR(NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Initializing the data
	memset(this->name, 0, NAME_LEN);
	this->number = 0;

	//Binding the member functions
	this->Random = &NODE_METHOD_Random;

	return ;
}

void NODE_METHOD_DESTRUCTOR(NODE *this)
{	
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	return ;
}

void NODE_METHOD_Random(NODE *this)
{
	int len = 0;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	while(len == 0){
		len = rand()%8;
	}

	for (int i=0 ; i<len ; i++){
		(this->name)[i] = letterCollection[rand()%62];
	}
	(this->name)[len] = 0;

	this->number = rand()%10000;

	return ;
}


//Function Defitions for struct _ARRAY
void ARRAY_METHOD_CONSTRUCTOR(ARRAY *this, int sizeArg)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Exception Handling
	if (sizeArg < 1){
		PRINTF_ERROR("ERROR: size is smaller than 0.\n");
		return ;
	}

	//Initializing the data values
	this->nodeArray = (NODE *)malloc(sizeof(NODE)*(sizeArg));
	this->size = sizeArg;
	for (int i=0 ; i<this->size ; i++){
		NODE_METHOD_CONSTRUCTOR(this->nodeArray + i);
	}

	//Binding the method functions
	this->Fill_Random = &ARRAY_METHOD_Fill_Random;
	this->Print = &ARRAY_METHOD_Print;
	this->Copy_to_Raw_Array = &ARRAY_METHOD_Copy_to_Raw_Array;
	this->Sort = &ARRAY_METHOD_Sort;

	srand((unsigned int)time(NULL));

	return ;
}

void ARRAY_METHOD_DESTRUCTOR(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	for (int i=0 ; i<this->size ; i++){
		NODE_METHOD_DESTRUCTOR(this->nodeArray + i);
	}

	free(this->nodeArray);
	this->nodeArray = NULL;
	this->size = 0;

	return ;
}

ARRAY *ARRAY_METHOD_Fill_Random(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	for (int i=0 ; i<this->size ; i++){
		(this->nodeArray)[i].Random(this->nodeArray + i);
	}

	return this;
}

void ARRAY_METHOD_Print(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	for (int i=0 ; i<this->size ; i++){
		printf("[%d] Name: %s, Number: %d\n", i
											, (this->nodeArray)[i].name
											, (this->nodeArray)[i].number);
	}

	return ;
}

ARRAY *ARRAY_METHOD_Copy_to_Raw_Array(ARRAY *this, NODE *dest)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (dest == NULL){
		PRINTF_ERROR("ERROR: 'dest' is NULL.\n");
		return NULL;
	}

	memcpy(dest, this->nodeArray, sizeof(NODE)*(this->size));

	return this;
}

int DFS_InorderTraversal_Sorting
(ARRAY *this, BST *inputBST, BST_NODE *inputNode)
{
	BST_NODE *currentNode = inputNode;
	BST_NODE *tempNode = NULL;

	if (currentNode->leftChild != NULL){
		DFS_InorderTraversal_Sorting(this, inputBST, currentNode->leftChild);
	}

	tempNode = currentNode;
	while(tempNode->nextFriend != NULL){
		memcpy((this->nodeArray)[this->currentIndex].name,
				tempNode->key, NAME_LEN);
		(this->nodeArray)[this->currentIndex].number = tempNode->data;
		this->currentIndex += 1;
		tempNode = tempNode->nextFriend;
	}

	memcpy((this->nodeArray)[this->currentIndex].name,
			tempNode->key, NAME_LEN);
	(this->nodeArray)[this->currentIndex].number = tempNode->data;
	this->currentIndex += 1;

	if (currentNode->rightChild != NULL){
		DFS_InorderTraversal_Sorting(this, inputBST, currentNode->rightChild);
	}

	return 0;
}

int InorderTraversal(ARRAY *this, BST *inputBST)
{
	this->currentIndex = 0;
	DFS_InorderTraversal_Sorting(this, inputBST, inputBST->root);

	return 0;
}

ARRAY *ARRAY_METHOD_Sort(ARRAY *this)
{
	BST sortingBST;
	BST_METHOD_CONSTRUCTOR(&sortingBST);

	for (int i=0 ; i<this->size ; i++){
		sortingBST.Insert(&sortingBST, (this->nodeArray)[i].name, (this->nodeArray)[i].number);
	}
	assert(this->size == sortingBST.size);

	InorderTraversal(this, &sortingBST);

	BST_METHOD_DESTRUCTOR(&sortingBST);
	return this;
}
