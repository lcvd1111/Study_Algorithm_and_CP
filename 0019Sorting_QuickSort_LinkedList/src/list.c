#include "list.h"

static char letterCollection[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

//Function Definitions
void LIST_NODE_METHOD_CONSTRUCTOR(LIST_NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	memset(this->name, 0, NAME_LEN);
	this->number = 0;
	this->prev = NULL;
	this->next = NULL;

	//Binding the method Functions
	this->Random = &LIST_NODE_METHOD_Random;

	return ;
}

void LIST_NODE_METHOD_DESTRUCTOR(LIST_NODE *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	return ;
}

void LIST_NODE_METHOD_Random(LIST_NODE *this)
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

void LIST_METHOD_CONSTRUCTOR(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	this->begin = this->end = NULL;
	this->size = 0;

	//Binding the method functions
	this->Print = &LIST_METHOD_Print;
	this->Size = &LIST_METHOD_Size;
	this->Add_One_Random = &LIST_METHOD_Add_One_Random;
	this->Add_Random = &LIST_METHOD_Add_Random;
	this->Sort = &LIST_METHOD_Sort;
	this->Copy_to_Array = &LIST_METHOD_Copy_to_Array;

	srand((unsigned int)time(NULL));

	return ;
}

void LIST_METHOD_DESTRUCTOR(LIST *this)
{
	LIST_NODE *temp = NULL;
	LIST_NODE *temp_next = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//When the list is empty currently.
	if (this->size == 0){
		return ;
	}

	//When the list is not empty currently.
	temp = this->begin;

	while(temp != NULL){
		temp_next = temp->next;
		LIST_NODE_METHOD_DESTRUCTOR(temp);
		free(temp);
		temp = temp_next;
	}

	this->begin = this->end = NULL;

	return ;
}

LIST *LIST_METHOD_Print(LIST *this)
{
	LIST_NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	temp = this->begin;

	for (int i=0 ; i<this->size ; i++){
		printf("[%d] Name: %s Number: %d\n"
				, i, temp->name, temp->number);
		temp = temp->next;
	}

	return this;
}

int LIST_METHOD_Size(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return -1;
	}

	return (this->size);
}

LIST *LIST_METHOD_Add_One_Random(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//When the list is empty currently.
	if (this->size == 0){
		assert(this->begin == NULL && this->end == NULL);
		this->begin = (LIST_NODE *)malloc(sizeof(LIST_NODE));
		this->end = this->begin;
		this->size = 1;
		LIST_NODE_METHOD_CONSTRUCTOR(this->begin);
		((this->begin)->Random)(this->begin);
		return this;
	}

	//When the list is not empty currently.
	this->end->next = (LIST_NODE *)malloc(sizeof(LIST_NODE));
	this->size += 1;
	LIST_NODE_METHOD_CONSTRUCTOR(this->end->next);
	this->end->next->prev = this->end;
	this->end = this->end->next;
	(this->end->Random)(this->end);

	return this;
}

LIST *LIST_METHOD_Add_Random(LIST *this, int sizeArg)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	//Exception Handling
	if (sizeArg < 0){
		PRINTF_ERROR("ERROR: sizeArg < 0.\n");
		return NULL;
	}
	
	for (int i=0 ; i<sizeArg ; i++){
		((*this).Add_One_Random)(this);
	}

	return this;
}

int Partition(LIST *this, LIST_NODE *beginNode, int elementSize, int *pivotIndex_return, LIST_NODE **pivotNode_return)
{
	int leftIndex=0, rightIndex=elementSize-1;
	LIST_NODE *leftNode=beginNode, *rightNode=beginNode;
	for (int i=0 ; i<rightIndex ; i++){
		rightNode = rightNode->next;
	}
	LIST_NODE *pivotNode = rightNode;

	//Variables for beins used as buffer for swapping
	LIST_NODE bufferNode;

	while(1){
		while (strcmp(leftNode->name, pivotNode->name)<0){
			leftNode = leftNode->next;
			leftIndex++;
		}

		while (strcmp(rightNode->name, pivotNode->name)>=0){
			rightNode = rightNode->prev;
			rightIndex--;

			if (rightIndex < 0){
				break;
			}
		}

		assert(leftIndex != rightIndex);

		if (leftIndex < rightIndex){
			memcpy(bufferNode.name, leftNode->name, NAME_LEN);
			bufferNode.number = leftNode->number;

			memcpy(leftNode->name, rightNode->name, NAME_LEN);
			leftNode->number = rightNode->number;

			memcpy(rightNode->name, bufferNode.name, NAME_LEN);
			rightNode->number = bufferNode.number;
			continue;
		}
		else if (leftIndex > rightIndex){
			memcpy(bufferNode.name, leftNode->name, NAME_LEN);
			bufferNode.number = leftNode->number;

			memcpy(leftNode->name, pivotNode->name, NAME_LEN);
			leftNode->number = pivotNode->number;

			memcpy(pivotNode->name, bufferNode.name, NAME_LEN);
			pivotNode->number = bufferNode.number;
			break;
		}
	}

	*pivotIndex_return = leftIndex;
	*pivotNode_return = leftNode;

	return 0;
}

int DFS_Recursive(LIST *this, LIST_NODE *beginNode, int elementSize)
{
	int pivotIndex = 0;
	LIST_NODE *pivotNode = NULL;

	int leftChild_elementSize=0, rightChild_elementSize=0;
	LIST_NODE *leftChild_beginNode=NULL, *rightChild_beginNode=NULL;

	//Base Case
	if ((elementSize <= 1) || (beginNode == NULL)){
		return 0;
	}

	if (Partition(this, beginNode, elementSize, &pivotIndex, &pivotNode)){
		PRINTF_ERROR("ERROR: 'Partition( )' function failed.\n");
		return -1;
	}

	leftChild_elementSize = pivotIndex;
	leftChild_beginNode = beginNode;
	DFS_Recursive(this, leftChild_beginNode, leftChild_elementSize);

	rightChild_elementSize = elementSize - pivotIndex - 1;
	rightChild_beginNode = pivotNode->next;
	DFS_Recursive(this, rightChild_beginNode, rightChild_elementSize);

	return 0;
}

LIST *LIST_METHOD_Sort(LIST *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
	}

	DFS_Recursive(this, this->begin, this->size);

	return this;
}

LIST *LIST_METHOD_Copy_to_Array(LIST *this, LIST_NODE *dest)
{
	LIST_NODE *temp = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
	}

	//When the list is empty
	if (this->size == 0){
		return this;
	}

	temp = this->begin;

	for (int i=0 ; i<this->size ; i++){
		memcpy(dest+i, temp, sizeof(LIST_NODE));
		temp = temp->next;
	}

	return this;
}

