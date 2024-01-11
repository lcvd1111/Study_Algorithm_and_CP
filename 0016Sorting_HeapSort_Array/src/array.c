#include "array.h"

//Function Definitions
void ARRAY_CONSTRUCTOR(ARRAY *this, int sizeArg)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	if (sizeArg < 1){
		PRINTF_ERROR("ERROR: 'sizeArg' is smaller than 1.\n");
		return ;
	}

	this->nodeArray = (NODE *)malloc(sizeof(NODE)*sizeArg);
	for (int i=0 ; i<sizeArg ; i++){
		NODE_CONSTRUCTOR(this->nodeArray + i);
	}
	this->size = sizeArg;
	srand((unsigned int)time(NULL));

	//Binding the method functions
	this->FillRandom = &ARRAY_METHOD_FillRandom;
	this->Sort = &ARRAY_METHOD_Sort;
	this->Print = &ARRAY_METHOD_Print;
	this->Size = &ARRAY_METHOD_Size;

	return ;
}

void ARRAY_DESTRUCTOR(ARRAY *this)
{
	//Exception Handling
	if (this==NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	//Exception Handling
	if (this->nodeArray == NULL){
		PRINTF_ERROR("ERROR: 'this->nodeArray' is NULL.\n");
		return ;
	}

	free(this->nodeArray);
	this->nodeArray = NULL;

	return ;
}

ARRAY *ARRAY_METHOD_FillRandom(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	for (int i=0 ; i<this->size ; i++){
		(this->nodeArray)[i].Random(this->nodeArray + i);
	}

	return NULL;
}

void ARRAY_METHOD_Print(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return ;
	}

	for (int i=0 ; i<this->size ; i++){
		printf(COLOR_BLACK "[%d] Name: %s, Number: %d\n" COLOR_BLACK,
				i, (this->nodeArray)[i].name, (this->nodeArray)[i].number);
	}

	return ;
}

ARRAY *ARRAY_METHOD_Sort(ARRAY *this)
{
	PQ sortingPQ;
	int level=0, size = 0;
	NODE *newArray = NULL;

	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return NULL;
	}

	level = 0;
	size = 1;
	while(size < this->size){
		size = size * 2;
		level++;
	}
	level++;

	PQ_CONSTRUCTOR(&sortingPQ, level);

	for (int i=0 ; i<this->size ; i++){
		sortingPQ.Enqueue(&sortingPQ, (this->nodeArray)+i);
	}

	newArray = (NODE *)malloc(sizeof(NODE)*(this->size));
	for (int i=0 ; i<this->size ; i++){
		memcpy(newArray+i, sortingPQ.Dequeue(&sortingPQ), sizeof(NODE));
	}
	free(this->nodeArray);
	this->nodeArray = newArray;

	PQ_DESTRUCTOR(&sortingPQ);
	return NULL;
}

int ARRAY_METHOD_Size(ARRAY *this)
{
	//Exception Handling
	if (this == NULL){
		PRINTF_ERROR("ERROR: 'this' is NULL.\n");
		return -1;
	}

	return this->size;
}
